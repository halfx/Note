08048464  55                push ebp
08048465  89E5              mov ebp,esp
08048467  53                push ebx
08048468  81EC34040000      sub esp,0x434
0804846E  83E4F0            and esp,byte -0x10
08048471  B800000000        mov eax,0x0
08048476  29C4              sub esp,eax
08048478  C745F464870408    mov dword [ebp-0xc],0x8048764 # U[[ZRcWfcXVM$l"#
0804847F  C7042475870408    mov dword [esp],0x8048775 # Please enter your password:
08048486  E8CDFEFFFF        call dword 0x8048358 # func_358("Please enter ***");
0804848B  8945F0            mov [ebp-0x10],eax # 把返回值放到ebp-0x10
0804848E  C785E4FBFFFF0000  mov dword [ebp-0x41c],0x0
         -0000
08048498  8B45F0            mov eax,[ebp-0x10]
0804849B  890424            mov [esp],eax
0804849E  E8C5FEFFFF        call dword 0x8048368 # 函数参数 var_10 : ebp-0x10    func_368(var_10)
080484A3  48                dec eax
080484A4  3985E4FBFFFF      cmp [ebp-0x41c],eax 
080484AA  7347              jnc 0x80484f3 # var_41c >= eax，执行跳转,  if(var_41c >= (func_368(var_10) - 1)) then jmp 80484f3 
080484AC  81BDE4FBFFFFFB03  cmp dword [ebp-0x41c],0x3fb #
         -0000
080484B6  7602              jna 0x80484ba # if(var_41c <= 0x3fb) then jmp 80484ba  else jmp 80484f3
080484B8  EB39              jmp short 0x80484f3

080484BA  8D85E8FBFFFF      lea eax,[ebp-0x418] # 这里 ebp-0x418应该是个数组的首地址
080484C0  89C3              mov ebx,eax
080484C2  039DE4FBFFFF      add ebx,[ebp-0x41c] # ebx = &var_418[var_41c]
080484C8  8B85E4FBFFFF      mov eax,[ebp-0x41c] #
080484CE  0345F0            add eax,[ebp-0x10]  # eax = var_41c + var_10
080484D1  8D4801            lea ecx,[eax+0x1]   # ecx = var_41c + var_10 + 1
080484D4  8B85E4FBFFFF      mov eax,[ebp-0x41c] # eax = var_41c
080484DA  0345F0            add eax,[ebp-0x10]  # eax = var_41c + var_10
080484DD  0FB610            movzx edx,byte [eax] #  dl = byte[var_41c + var_10]
080484E0  0FB601            movzx eax,byte [ecx] #  al = byte[var_41c + var_10 + 1]
080484E3  28D0              sub al,dl #  al = al - dl
080484E5  045A              add al,0x5a # al = al + 0x5a
080484E7  8803              mov [ebx],al  # var_418[var_41c] = byte[var_41c + var_10 + 1] - byte[var_41c + var_10] + 0x5a
080484E9  8D85E4FBFFFF      lea eax,[ebp-0x41c]
080484EF  FF00              inc dword [eax] # var_41c++
080484F1  EBA5              jmp short 0x8048498 # goto 0x8048498

080484F3  8D85E8FBFFFF      lea eax,[ebp-0x418]  # 
080484F9  89C2              mov edx,eax
080484FB  0395E4FBFFFF      add edx,[ebp-0x41c] # edx = &var_418[var_41c]
08048501  8B85E4FBFFFF      mov eax,[ebp-0x41c] # eax = var_41c
08048507  0345F0            add eax,[ebp-0x10]  # eax = var_10 + var_41c
0804850A  0FB600            movzx eax,byte [eax] # al = byte[var_10 + var_41c]
0804850D  C0F804            sar al,0x4           # sar: 算术右移4位，当值为负，高位补1，当值为正，高位补0
08048510  240F              and al,0xf           # al = al and 0xf
08048512  0421              add al,0x21          # al = al + 0x21
08048514  8802              mov [edx],al         # var_418[var_41c] = (byte[var_10 + var_41c] >>4) & 0xf + 0x21
08048516  8D85E9FBFFFF      lea eax,[ebp-0x417]  # 
0804851C  89C2              mov edx,eax
0804851E  0395E4FBFFFF      add edx,[ebp-0x41c]  # edx = &var_417[var_41c]
08048524  8B85E4FBFFFF      mov eax,[ebp-0x41c]
0804852A  0345F0            add eax,[ebp-0x10]   # eax = var_10 + var_41c
0804852D  0FB600            movzx eax,byte [eax] # al = byte[var_10 + var_41c]
08048530  240F              and al,0xf           # al = al and 0xf
08048532  0421              add al,0x21          # al = al + 0x21
08048534  8802              mov [edx],al         # var_417[var_41c] = byte[var_10 + var41c] & 0xf + 0x21
08048536  8D85EAFBFFFF      lea eax,[ebp-0x416]  #
0804853C  0385E4FBFFFF      add eax,[ebp-0x41c]  # eax = &var_416[var_41c]
08048542  C60000            mov byte [eax],0x0   # var_416[var_41c] = 0 
08048545  C785E4FBFFFF0000  mov dword [ebp-0x41c],0x0 # var_41c = 0
         -0000
0804854F  8D85E8FBFFFF      lea eax,[ebp-0x418]
08048555  890424            mov [esp],eax
08048558  E80BFEFFFF        call dword 0x8048368 # func_368(&var_418)
0804855D  48                dec eax              #
0804855E  3985E4FBFFFF      cmp [ebp-0x41c],eax  #
08048564  7205              jc 0x804856b         # if(var_41c < (func_368(&var_418) - 1)) goto 0x804856b else goto 0x8048606
08048566  E99B000000        jmp dword 0x8048606

0804856B  8D85E8FBFFFF      lea eax,[ebp-0x418]  # 
08048571  89C1              mov ecx,eax
08048573  038DE4FBFFFF      add ecx,[ebp-0x41c]  # ecx = &var_418[var_41c]
08048579  8D85E8FBFFFF      lea eax,[ebp-0x418]
0804857F  89C2              mov edx,eax
08048581  0395E4FBFFFF      add edx,[ebp-0x41c]  # edx = &var_418[var_41c]
08048587  8D85E9FBFFFF      lea eax,[ebp-0x417]
0804858D  0385E4FBFFFF      add eax,[ebp-0x41c]  # eax = &var_417[var_41c]
08048593  0FB600            movzx eax,byte [eax] # al = byte[eax]
08048596  3202              xor al,[edx]         # al = al ^ [edx] = byte[var_417[var_41c]] ^[var_418[var_41c]]
08048598  8801              mov [ecx],al         # var_418[var_41c] = byte[var_417[var_41c]] ^ var_418[var_41c];
0804859A  8D85E9FBFFFF      lea eax,[ebp-0x417]  #
080485A0  89C1              mov ecx,eax
080485A2  038DE4FBFFFF      add ecx,[ebp-0x41c]  # ecx = &var_417[var_41c]
080485A8  8D85E9FBFFFF      lea eax,[ebp-0x417]  # 
080485AE  89C2              mov edx,eax
080485B0  0395E4FBFFFF      add edx,[ebp-0x41c]  # edx = &var_417[var_41c]
080485B6  8D85E8FBFFFF      lea eax,[ebp-0x418]
080485BC  0385E4FBFFFF      add eax,[ebp-0x41c]  # eax = &var_418[var_41c]
080485C2  0FB600            movzx eax,byte [eax] # al = byte[var_418[var_41c]]
080485C5  3202              xor al,[edx]         # al = al ^ [edx]
080485C7  8801              mov [ecx],al         # var_417[var_41c] = byte[var_418[var_41c]] ^ var_417[var_41c]
080485C9  8D85E8FBFFFF      lea eax,[ebp-0x418]  # 
080485CF  89C1              mov ecx,eax
080485D1  038DE4FBFFFF      add ecx,[ebp-0x41c]  # ecx = &var_418[var_41c]
080485D7  8D85E8FBFFFF      lea eax,[ebp-0x418]  #
080485DD  89C2              mov edx,eax
080485DF  0395E4FBFFFF      add edx,[ebp-0x41c]  # edx = &var_418[var_41c]
080485E5  8D85E9FBFFFF      lea eax,[ebp-0x417]
080485EB  0385E4FBFFFF      add eax,[ebp-0x41c]  # eax = &var_417[var_41c]
080485F1  0FB600            movzx eax,byte [eax] # al = byte[var_417[var_41c]]
080485F4  3202              xor al,[edx]         #
080485F6  8801              mov [ecx],al         # var_418[var_41c] = var_418[var_41c] ^ byte[var_417[var_41c]]
080485F8  8D85E4FBFFFF      lea eax,[ebp-0x41c]
080485FE  830002            add dword [eax],byte +0x2 # var_41c = var_41c + 2
08048601  E949FFFFFF        jmp dword 0x804854f


08048606  8D95E8FBFFFF      lea edx,[ebp-0x418]  # edx = &var_418
0804860C  8B45F4            mov eax,[ebp-0xc]    # eax = var_c
0804860F  89442404          mov [esp+0x4],eax
08048613  891424            mov [esp],edx
08048616  E81DFDFFFF        call dword 0x8048338 # func338(&var_418, var_c)
0804861B  85C0              test eax,eax      
0804861D  751A              jnz 0x8048639        # if (func338(&var_418, var_c) != 0) goto 8048639
0804861F  C7042492870408    mov dword [esp],0x8048792 #
08048626  E85DFDFFFF        call dword 0x8048388      # func388("welcome\n\x00")
0804862B  C704249B870408    mov dword [esp],0x804879b
08048632  E811FDFFFF        call dword 0x8048348      # func348("/bin/sh\x00")
08048637  EB0C              jmp short 0x8048645

08048639  C70424A3870408    mov dword [esp],0x80487a3
08048640  E843FDFFFF        call dword 0x8048388      # func388("Invalid password!")

08048645  B800000000        mov eax,0x0
0804864A  8B5DFC            mov ebx,[ebp-0x4]
0804864D  C9                leave
0804864E  C3                ret


0804864F  90                nop
08048650  55                push ebp
08048651  89E5              mov ebp,esp
08048653  57                push edi
08048654  56                push esi
08048655  31F6              xor esi,esi
08048657  53                push ebx
08048658  83EC0C            sub esp,byte +0xc
0804865B  E8A0000000        call dword 0x8048700
08048660  81C344120000      add ebx,0x1244
08048666  E8A5FCFFFF        call dword 0x8048310
0804866B  8D9314FFFFFF      lea edx,[ebx-0xec]
08048671  8D8314FFFFFF      lea eax,[ebx-0xec]
08048677  29C2              sub edx,eax
08048679  C1FA02            sar edx,0x2
0804867C  39D6              cmp esi,edx
0804867E  731C              jnc 0x804869c
08048680  89D7              mov edi,edx
08048682  8DB42600000000    lea esi,[esi+0x0]
08048689  8DBC2700000000    lea edi,[edi+0x0]
08048690  FF94B314FFFFFF    call dword near [ebx+esi*4-0xec]
08048697  46                inc esi
08048698  39FE              cmp esi,edi
0804869A  72F4              jc 0x8048690
0804869C  83C40C            add esp,byte +0xc
0804869F  5B                pop ebx
080486A0  5E                pop esi
080486A1  5F                pop edi
080486A2  5D                pop ebp
080486A3  C3                ret
080486A4  8DB600000000      lea esi,[esi+0x0]
080486AA  8DBF00000000      lea edi,[edi+0x0]
080486B0  55                push ebp
080486B1  89E5              mov ebp,esp
080486B3  83EC08            sub esp,byte +0x8
080486B6  891C24            mov [esp],ebx
080486B9  E842000000        call dword 0x8048700
080486BE  81C3E6110000      add ebx,0x11e6
080486C4  89742404          mov [esp+0x4],esi
080486C8  8D8314FFFFFF      lea eax,[ebx-0xec]
080486CE  8D9314FFFFFF      lea edx,[ebx-0xec]
080486D4  29D0              sub eax,edx
080486D6  C1F802            sar eax,0x2
080486D9  85C0              test eax,eax
080486DB  8D70FF            lea esi,[eax-0x1]
080486DE  7510              jnz 0x80486f0
080486E0  E85B000000        call dword 0x8048740
080486E5  8B1C24            mov ebx,[esp]
080486E8  8B742404          mov esi,[esp+0x4]
080486EC  89EC              mov esp,ebp
080486EE  5D                pop ebp
080486EF  C3                ret
080486F0  FF94B314FFFFFF    call dword near [ebx+esi*4-0xec]
080486F7  89F0              mov eax,esi
080486F9  4E                dec esi
080486FA  85C0              test eax,eax
080486FC  75F2              jnz 0x80486f0
080486FE  EBE0              jmp short 0x80486e0
08048700  8B1C24            mov ebx,[esp]
08048703  C3                ret
08048704  90                nop
08048705  90                nop
08048706  90                nop
08048707  90                nop
08048708  90                nop
08048709  90                nop
0804870A  90                nop
0804870B  90                nop
0804870C  90                nop
0804870D  90                nop
0804870E  90                nop
0804870F  90                nop
08048710  55                push ebp
08048711  89E5              mov ebp,esp
08048713  53                push ebx
08048714  83EC04            sub esp,byte +0x4
08048717  BB90980408        mov ebx,0x8049890
0804871C  A190980408        mov eax,[0x8049890]
08048721  83F8FF            cmp eax,byte -0x1
08048724  7416              jz 0x804873c
08048726  8D7600            lea esi,[esi+0x0]
08048729  8DBC2700000000    lea edi,[edi+0x0]
08048730  83EB04            sub ebx,byte +0x4
08048733  FFD0              call eax
08048735  8B03              mov eax,[ebx]
08048737  83F8FF            cmp eax,byte -0x1
0804873A  75F4              jnz 0x8048730
0804873C  58                pop eax
0804873D  5B                pop ebx
0804873E  5D                pop ebp
0804873F  C3                ret
08048740  55                push ebp
08048741  89E5              mov ebp,esp
08048743  53                push ebx
08048744  E800000000        call dword 0x8048749
08048749  5B                pop ebx
0804874A  81C35B110000      add ebx,0x115b
08048750  52                push edx
08048751  E89AFCFFFF        call dword 0x80483f0
08048756  8B5DFC            mov ebx,[ebp-0x4]
08048759  C9                leave
0804875A  C3                ret
0804875B  0003              add [ebx],al
0804875D  0000              add [eax],al
0804875F  0001              add [ecx],al
08048761  0002              add [edx],al
08048763  00555B            add [ebp+0x5b],dl
08048766  5B                pop ebx
08048767  5A                pop edx
08048768  52                push edx
08048769  635766            arpl [edi+0x66],dx
0804876C  635856            arpl [eax+0x56],bx
0804876F  4D                dec ebp
08048770  246C              and al,0x6c
08048772  2223              and ah,[ebx]
08048774  00506C            add [eax+0x6c],dl
08048777  6561              gs popad
08048779  7365              jnc 0x80487e0
0804877B  20656E            and [ebp+0x6e],ah
0804877E  7465              jz 0x80487e5
08048780  7220              jc 0x80487a2
08048782  796F              jns 0x80487f3
08048784  7572              jnz 0x80487f8
08048786  207061            and [eax+0x61],dh
08048789  7373              jnc 0x80487fe
0804878B  776F              ja 0x80487fc
0804878D  7264              jc 0x80487f3
0804878F  3A20              cmp ah,[eax]
08048791  005765            add [edi+0x65],dl
08048794  6C                insb
08048795  636F6D            arpl [edi+0x6d],bp
08048798  650A00            or al,[gs:eax]
0804879B  2F                das
0804879C  62696E            bound ebp,[ecx+0x6e]
0804879F  2F                das
080487A0  7368              jnc 0x804880a
080487A2  00496E            add [ecx+0x6e],cl
080487A5  7661              jna 0x8048808
080487A7  6C                insb
080487A8  6964207061737377  imul esp,[eax+0x70],dword 0x77737361
080487B0  6F                outsd
080487B1  7264              jc 0x8048817
080487B3  210A              and [edx],ecx
080487B5  0000              add [eax],al
080487B7  0000              add [eax],al
080487B9  0000              add [eax],al
080487BB  0000              add [eax],al
080487BD  0000              add [eax],al
080487BF  009C9804080000    add [eax+ebx*4+0x804],bl
080487C6  0000              add [eax],al
080487C8  0100              add [eax],eax
080487CA  0000              add [eax],al
080487CC  2400              and al,0x0
080487CE  0000              add [eax],al
080487D0  0C00              or al,0x0
080487D2  0000              add [eax],al
080487D4  108304080D00      adc [ebx+0xd0804],al
080487DA  0000              add [eax],al
080487DC  40                inc eax
080487DD  870408            xchg eax,[eax+ecx]
080487E0  0400              add al,0x0
080487E2  0000              add [eax],al
080487E4  48                dec eax
080487E5  81040805000000    add dword [eax+ecx],0x5
080487EC  2482              and al,0x82
080487EE  0408              add al,0x8
080487F0  06                push es
080487F1  0000              add [eax],al
080487F3  00848104080A00    add [ecx+eax*4+0xa0804],al
080487FA  0000              add [eax],al
080487FC  7D00              jnl 0x80487fe
080487FE  0000              add [eax],al
08048800  0B00              or eax,[eax]
08048802  0000              add [eax],al
08048804  1000              adc [eax],al
08048806  0000              add [eax],al
08048808  1500000000        adc eax,0x0
0804880D  0000              add [eax],al
0804880F  0003              add [ebx],al
08048811  0000              add [eax],al
08048813  00A49804080200    add [eax+ebx*4+0x20804],ah
0804881A  0000              add [eax],al
0804881C  3000              xor [eax],al
0804881E  0000              add [eax],al
08048820  1400              adc al,0x0
08048822  0000              add [eax],al
08048824  1100              adc [eax],eax
08048826  0000              add [eax],al
08048828  17                pop ss
08048829  0000              add [eax],al
0804882B  00E0              add al,ah
0804882D  82                db 0x82
0804882E  0408              add al,0x8
08048830  1100              adc [eax],eax
08048832  0000              add [eax],al
08048834  D88204081200      fadd dword [edx+0x120804]
0804883A  0000              add [eax],al
0804883C  0800              or [eax],al
0804883E  0000              add [eax],al
08048840  1300              adc eax,[eax]
08048842  0000              add [eax],al
08048844  0800              or [eax],al
08048846  0000              add [eax],al
08048848  FE                db 0xfe
08048849  FF                db 0xff
0804884A  FF6FB8            jmp dword far [edi-0x48]
0804884D  82                db 0x82
0804884E  0408              add al,0x8
08048850  FF                db 0xff
08048851  FF                db 0xff
08048852  FF6F01            jmp dword far [edi+0x1]
08048855  0000              add [eax],al
08048857  00F0              add al,dh
08048859  FF                db 0xff
0804885A  FF6FA2            jmp dword far [edi-0x5e]
0804885D  82                db 0x82
0804885E  0408              add al,0x8
08048860  0000              add [eax],al
08048862  0000              add [eax],al
08048864  0000              add [eax],al
08048866  0000              add [eax],al
08048868  0000              add [eax],al
0804886A  0000              add [eax],al
0804886C  0000              add [eax],al
0804886E  0000              add [eax],al
08048870  0000              add [eax],al
08048872  0000              add [eax],al
08048874  0000              add [eax],al
08048876  0000              add [eax],al
08048878  0000              add [eax],al
0804887A  0000              add [eax],al
0804887C  0000              add [eax],al
0804887E  0000              add [eax],al
08048880  0000              add [eax],al
08048882  0000              add [eax],al
08048884  0000              add [eax],al
08048886  0000              add [eax],al
08048888  0000              add [eax],al
0804888A  0000              add [eax],al
0804888C  0000              add [eax],al
0804888E  0000              add [eax],al
08048890  FF                db 0xff
08048891  FF                db 0xff
08048892  FF                db 0xff
08048893  FF00              inc dword [eax]
08048895  0000              add [eax],al
08048897  00FF              add bh,bh
08048899  FF                db 0xff
0804889A  FF                db 0xff
0804889B  FF00              inc dword [eax]
0804889D  0000              add [eax],al
0804889F  0000              add [eax],al
080488A1  0000              add [eax],al
080488A3  00C8              add al,cl
080488A5  97                xchg eax,edi
080488A6  0408              add al,0x8
080488A8  0000              add [eax],al
080488AA  0000              add [eax],al
080488AC  0000              add [eax],al
080488AE  0000              add [eax],al
080488B0  3E8304084E        add dword [ds:eax+ecx],byte +0x4e
080488B5  8304085E          add dword [eax+ecx],byte +0x5e
080488B9  8304086E          add dword [eax+ecx],byte +0x6e
080488BD  8304087E          add dword [eax+ecx],byte +0x7e
080488C1  8304088E          add dword [eax+ecx],byte -0x72
080488C5  83040800          add dword [eax+ecx],byte +0x0
080488C9  0000              add [eax],al
080488CB  0000              add [eax],al
080488CD  47                inc edi
080488CE  43                inc ebx
080488CF  43                inc ebx
080488D0  3A20              cmp ah,[eax]
080488D2  28474E            sub [edi+0x4e],al
080488D5  55                push ebp
080488D6  2920              sub [eax],esp
080488D8  332E              xor ebp,[esi]
080488DA  332E              xor ebp,[esi]
080488DC  3520284465        xor eax,0x65442820
080488E1  626961            bound ebp,[ecx+0x61]
080488E4  6E                outsb
080488E5  2031              and [ecx],dh
080488E7  3A33              cmp dh,[ebx]
080488E9  2E332E            xor ebp,[cs:esi]
080488EC  352D313329        xor eax,0x2933312d
080488F1  0000              add [eax],al
080488F3  47                inc edi
080488F4  43                inc ebx
080488F5  43                inc ebx
080488F6  3A20              cmp ah,[eax]
080488F8  28474E            sub [edi+0x4e],al
080488FB  55                push ebp
080488FC  2920              sub [eax],esp
080488FE  332E              xor ebp,[esi]
08048900  332E              xor ebp,[esi]
08048902  3520284465        xor eax,0x65442820
08048907  626961            bound ebp,[ecx+0x61]
0804890A  6E                outsb
0804890B  2031              and [ecx],dh
0804890D  3A33              cmp dh,[ebx]
0804890F  2E332E            xor ebp,[cs:esi]
08048912  352D313329        xor eax,0x2933312d
08048917  0000              add [eax],al
08048919  47                inc edi
0804891A  43                inc ebx
0804891B  43                inc ebx
0804891C  3A20              cmp ah,[eax]
0804891E  28474E            sub [edi+0x4e],al
08048921  55                push ebp
08048922  2920              sub [eax],esp
08048924  332E              xor ebp,[esi]
08048926  332E              xor ebp,[esi]
08048928  3520284465        xor eax,0x65442820
0804892D  626961            bound ebp,[ecx+0x61]
08048930  6E                outsb
08048931  2031              and [ecx],dh
08048933  3A33              cmp dh,[ebx]
08048935  2E332E            xor ebp,[cs:esi]
08048938  352D313329        xor eax,0x2933312d
0804893D  0000              add [eax],al
0804893F  47                inc edi
08048940  43                inc ebx
08048941  43                inc ebx
08048942  3A20              cmp ah,[eax]
08048944  28474E            sub [edi+0x4e],al
08048947  55                push ebp
08048948  2920              sub [eax],esp
0804894A  332E              xor ebp,[esi]
0804894C  332E              xor ebp,[esi]
0804894E  3520284465        xor eax,0x65442820
08048953  626961            bound ebp,[ecx+0x61]
08048956  6E                outsb
08048957  2031              and [ecx],dh
08048959  3A33              cmp dh,[ebx]
0804895B  2E332E            xor ebp,[cs:esi]
0804895E  352D313329        xor eax,0x2933312d
08048963  0000              add [eax],al
08048965  47                inc edi
08048966  43                inc ebx
08048967  43                inc ebx
08048968  3A20              cmp ah,[eax]
0804896A  28474E            sub [edi+0x4e],al
0804896D  55                push ebp
0804896E  2920              sub [eax],esp
08048970  332E              xor ebp,[esi]
08048972  332E              xor ebp,[esi]
08048974  3520284465        xor eax,0x65442820
08048979  626961            bound ebp,[ecx+0x61]
0804897C  6E                outsb
0804897D  2031              and [ecx],dh
0804897F  3A33              cmp dh,[ebx]
08048981  2E332E            xor ebp,[cs:esi]
08048984  352D313329        xor eax,0x2933312d
08048989  0000              add [eax],al
0804898B  47                inc edi
0804898C  43                inc ebx
0804898D  43                inc ebx
0804898E  3A20              cmp ah,[eax]
08048990  28474E            sub [edi+0x4e],al
08048993  55                push ebp
08048994  2920              sub [eax],esp
08048996  332E              xor ebp,[esi]
08048998  332E              xor ebp,[esi]
0804899A  3520284465        xor eax,0x65442820
0804899F  626961            bound ebp,[ecx+0x61]
080489A2  6E                outsb
080489A3  2031              and [ecx],dh
080489A5  3A33              cmp dh,[ebx]
080489A7  2E332E            xor ebp,[cs:esi]
080489AA  352D313329        xor eax,0x2933312d
080489AF  0000              add [eax],al
080489B1  47                inc edi
080489B2  43                inc ebx
080489B3  43                inc ebx
080489B4  3A20              cmp ah,[eax]
080489B6  28474E            sub [edi+0x4e],al
080489B9  55                push ebp
080489BA  2920              sub [eax],esp
080489BC  332E              xor ebp,[esi]
080489BE  332E              xor ebp,[esi]
080489C0  3520284465        xor eax,0x65442820
080489C5  626961            bound ebp,[ecx+0x61]
080489C8  6E                outsb
080489C9  2031              and [ecx],dh
080489CB  3A33              cmp dh,[ebx]
080489CD  2E332E            xor ebp,[cs:esi]
080489D0  352D313329        xor eax,0x2933312d
080489D5  0000              add [eax],al
080489D7  001C00            add [eax+eax],bl
080489DA  0000              add [eax],al
080489DC  0200              add al,[eax]
080489DE  0000              add [eax],al
080489E0  0000              add [eax],al
080489E2  0400              add al,0x0
080489E4  0000              add [eax],al
080489E6  0000              add [eax],al
080489E8  A083040822        mov al,[0x22080483]
080489ED  0000              add [eax],al
080489EF  0000              add [eax],al
080489F1  0000              add [eax],al
080489F3  0000              add [eax],al
080489F5  0000              add [eax],al
080489F7  002C00            add [eax+eax],ch
080489FA  0000              add [eax],al
080489FC  0200              add al,[eax]
080489FE  1509000004        adc eax,0x4000009
08048A03  0000              add [eax],al
08048A05  0000              add [eax],al
08048A07  004087            add [eax-0x79],al
08048A0A  0408              add al,0x8
08048A0C  1100              adc [eax],eax
08048A0E  0000              add [eax],al
08048A10  108304080B00      adc [ebx+0xb0804],al
08048A16  0000              add [eax],al
08048A18  C48304082200      les eax,[ebx+0x220804]
08048A1E  0000              add [eax],al
08048A20  0000              add [eax],al
08048A22  0000              add [eax],al
08048A24  0000              add [eax],al
08048A26  0000              add [eax],al
08048A28  2400              and al,0x0
08048A2A  0000              add [eax],al
08048A2C  0200              add al,[eax]
08048A2E  A6                cmpsb
08048A2F  0900              or [eax],eax
08048A31  000400            add [eax+eax],al
08048A34  0000              add [eax],al
08048A36  0000              add [eax],al
08048A38  56                push esi
08048A39  870408            xchg eax,[eax+ecx]
08048A3C  0500000025        add eax,0x25000000
08048A41  83040802          add dword [eax+ecx],byte +0x2
08048A45  0000              add [eax],al
08048A47  0000              add [eax],al
08048A49  0000              add [eax],al
08048A4B  0000              add [eax],al
08048A4D  0000              add [eax],al
08048A4F  0021              add [ecx],ah
08048A51  0000              add [eax],al
08048A53  0002              add [edx],al
08048A55  007900            add [ecx+0x0],bh
08048A58  0000              add [eax],al
08048A5A  9C                pushfd
08048A5B  0800              or [eax],al
08048A5D  00840800005F49    add [eax+ecx+0x495f0000],al
08048A64  4F                dec edi
08048A65  5F                pop edi
08048A66  7374              jnc 0x8048adc
08048A68  64696E5F75736564  imul ebp,[fs:esi+0x5f],dword 0x64657375
08048A70  0000              add [eax],al
08048A72  0000              add [eax],al
08048A74  007500            add [ebp+0x0],dh
08048A77  0000              add [eax],al
08048A79  0200              add al,[eax]
08048A7B  0000              add [eax],al
08048A7D  0000              add [eax],al
08048A7F  0401              add al,0x1
08048A81  0000              add [eax],al
08048A83  0000              add [eax],al
08048A85  A0830408C2        mov al,[0xc2080483]
08048A8A  8304082E          add dword [eax+ecx],byte +0x2e
08048A8E  2E2F              cs das
08048A90  7379              jnc 0x8048b0b
08048A92  7364              jnc 0x8048af8
08048A94  657073            gs jo 0x8048b0a
08048A97  2F                das
08048A98  693338362F65      imul esi,[ebx],dword 0x652f3638
08048A9E  6C                insb
08048A9F  662F              o16 das
08048AA1  7374              jnc 0x8048b17
08048AA3  61                popad
