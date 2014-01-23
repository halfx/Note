int main()
{ 
  var_c =  " U[[ZRcWfcXVM$l\"#"   /* size:16 */
  var_10 = func_358("Please enter your password:");
  var_41c = 0;
/*
label0:
  if(var_41c >= (func_368(var_10) - 1))
    goto label1;  // 80484f3
  else
  {
    if (var_41c <= 0x3fb)
      goto label2; // 80484ba
    else
      goto label1; //80484f3
  }

lable2:
  var_418[var_41c] = byte[var_41c + var_10 + 1] - byte[var_41c + var_10] + 0x5a;
  var_41c++;
  goto label0;

label1:
  var_418[var_41c] = (byte[var_10 + var_41c] >> 4) & 0xf + 0x21;
  var_417[var_41c] =  byte[var_10 + var_41c] & 0xf +0x21;
  var_416[var_41c] = 0;
  var_41c = 0;

lable5: 
  if(var_41c < (func_368(&var_418) - 1))
    goto label3; // 0x804856b
  else
    goto label4; // 0x8048606

label3:
  var_418[var_41c] = byte[var_417[var_41c]] ^ var_418[var_41c];
  var_417[var_41c] = byte[var_418[var_41c]] ^ var_417[var_41c];
  var_418[var_41c] = byte[var_417[var_41c]] ^ var_418[var_41c];
  var_41c += 2;
  goto label5; // 0x804854f

lable4:
  if(func338(&var_418, var_c) != 0)
    goto error;
  else
  {
    func388("welcome\n\x00");
    func348("/bin/sh\x00");
  }
error:
  func388("Invalid password!");
  exit
*/


  for(; (var_41c < func_368(var_10) - 1) && var_41c <= 0x3fb; var_41c++)
  {
    var_418[var_41c] = byte[var_41c + var_10 + 1] - byte[var_41c + var_10] + 0x5a;
  }

  var_418[var_41c] = (byte[var_10 + var_41c] >> 4) & 0xf + 0x21;
  var_417[var_41c] =  byte[var_10 + var_41c] & 0xf +0x21;
  var_416[var_41c] = 0;
  var_41c = 0;

  for(; var_41c < func_368(&var_418) - 1; ) /* func_368: strlen */
  {
    var_418[var_41c] = byte[var_417[var_41c]] ^ var_418[var_41c];
    var_417[var_41c] = byte[var_418[var_41c]] ^ var_417[var_41c];
    var_418[var_41c] = byte[var_417[var_41c]] ^ var_418[var_41c];
    var_41c += 2;
  }
  if (func338(&var_418, var_c) != 0)  /*func338: strcmp*/
    goto error;
  else
  {
    func388("welcome\n\x00");
    func348("/bin/sh\x00");
  }
error:
  exit

}

