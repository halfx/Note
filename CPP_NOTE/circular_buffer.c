圆形缓冲区的一个有用特性是：当一个数据元素被用掉后，其余数据元素不需要移动其存储位置。相反，一个非圆形缓冲区（例如一个普通的队列）在用掉一个数据元素后，其余数据元素需要向前搬移。换句话说，圆形缓冲区适合实现先进先出缓冲区，而非圆形缓冲区适合后进先出缓冲区。

圆形缓冲区适合于事先明确了缓冲区的最大容量的情形。扩展一个圆形缓冲区的容量，需要搬移其中的数据。因此一个缓冲区如果需要经常调整其容量，用链表实现更为合适。
写操作覆盖圆形缓冲区中未被处理的数据在某些情况下是允许的。特别是在多媒体处理时。例如，音频的生产者可以覆盖掉声卡尚未来得及处理的音频数据。

使用一位记录最后一次操作是读还是写。读写指针值相等情况下，如果最后一次操作为写入，那么缓冲区是满的；如果最后一次操作为读出，那么缓冲区是空。 这种策略的缺点是读写操作共享一个标志位，多线程时需要并发控制。
POSIX优化实现[编辑]
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
 
#define report_exceptional_condition() abort ()
 
struct ring_buffer
{
  void *address;
 
  unsigned long count_bytes;
  unsigned long write_offset_bytes;
  unsigned long read_offset_bytes;
};
 
//Warning order should be at least 12 for Linux
void
ring_buffer_create (struct ring_buffer *buffer, unsigned long order)
{
  char path[] = "/dev/shm/ring-buffer-XXXXXX";
  int file_descriptor;
  void *address;
  int status;
 
  file_descriptor = mkstemp (path);
  if (file_descriptor < 0)
    report_exceptional_condition ();
 
  status = unlink (path);
  if (status)
    report_exceptional_condition ();
 
  buffer->count_bytes = 1UL << order;
  buffer->write_offset_bytes = 0;
  buffer->read_offset_bytes = 0;
 
  status = ftruncate (file_descriptor, buffer->count_bytes);
  if (status)
    report_exceptional_condition ();
 
  buffer->address = mmap (NULL, buffer->count_bytes << 1, PROT_NONE,
                          MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
 
  if (buffer->address == MAP_FAILED)
    report_exceptional_condition ();
 
  address =
    mmap (buffer->address, buffer->count_bytes, PROT_READ | PROT_WRITE,
          MAP_FIXED | MAP_SHARED, file_descriptor, 0);
 
  if (address != buffer->address)
    report_exceptional_condition ();
 
  address = mmap (buffer->address + buffer->count_bytes,
                  buffer->count_bytes, PROT_READ | PROT_WRITE,
                  MAP_FIXED | MAP_SHARED, file_descriptor, 0);
 
  if (address != buffer->address + buffer->count_bytes)
    report_exceptional_condition ();
 
  status = close (file_descriptor);
  if (status)
    report_exceptional_condition ();
}
 
void
ring_buffer_free (struct ring_buffer *buffer)
{
  int status;
 
  status = munmap (buffer->address, buffer->count_bytes << 1);
  if (status)
    report_exceptional_condition ();
}
 
void *
ring_buffer_write_address (struct ring_buffer *buffer)
{
  /*** void pointer arithmetic is a constraint violation. ***/
  return buffer->address + buffer->write_offset_bytes;
}
 
void
ring_buffer_write_advance (struct ring_buffer *buffer,
                           unsigned long count_bytes)
{
  buffer->write_offset_bytes += count_bytes;
}
 
void *
ring_buffer_read_address (struct ring_buffer *buffer)
{
  return buffer->address + buffer->read_offset_bytes;
}
 
void
ring_buffer_read_advance (struct ring_buffer *buffer,
                          unsigned long count_bytes)
{
  buffer->read_offset_bytes += count_bytes;
 
  if (buffer->read_offset_bytes >= buffer->count_bytes)
    { /*如果读指针大于等于缓冲区长度，那些读写指针同时折返回[0, buffer_size]范围内  */
      buffer->read_offset_bytes -= buffer->count_bytes;
      buffer->write_offset_bytes -= buffer->count_bytes;
    }
}
 
unsigned long
ring_buffer_count_bytes (struct ring_buffer *buffer)
{
  return buffer->write_offset_bytes - buffer->read_offset_bytes;
}
 
unsigned long
ring_buffer_count_free_bytes (struct ring_buffer *buffer)
{
  return buffer->count_bytes - ring_buffer_count_bytes (buffer);
}
 
void
ring_buffer_clear (struct ring_buffer *buffer)
{
  buffer->write_offset_bytes = 0;
  buffer->read_offset_bytes = 0;
}
 
/*Note, that initial anonymous mmap() can be avoided - after initial mmap() for descriptor fd,
you can try mmap() with hinted address as (buffer->address + buffer->count_bytes) and if it fails -
another one with hinted address as (buffer->address - buffer->count_bytes).
Make sure MAP_FIXED is not used in such case, as under certain situations it could end with segfault.
The advantage of such approach is, that it avoids requirement to map twice the amount you need initially
(especially useful e.g. if you want to use hugetlbfs and the allowed amount is limited)
and in context of gcc/glibc - you can avoid certain feature macros
(MAP_ANONYMOUS usually requires one of: _BSD_SOURCE, _SVID_SOURCE or _GNU_SOURCE).*/