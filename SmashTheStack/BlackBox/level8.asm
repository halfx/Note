08048464  55                push ebp
08048465  89E5              mov ebp,esp
08048467  53                push ebx
08048468  81EC34040000      sub esp,0x434
0804846E  83E4F0            and esp,byte -0x10
08048471  B800000000        mov eax,0x0
08048476  29C4              sub esp,eax
08048478  C745F464870408    mov dword [ebp-0xc],0x8048764
0804847F  C7042475870408    mov dword [esp],0x8048775
08048486  E8CDFEFFFF        call dword 0x8048358
0804848B  8945F0            mov [ebp-0x10],eax
0804848E  C785E4FBFFFF0000  mov dword [ebp-0x41c],0x0
         -0000
08048498  8B45F0            mov eax,[ebp-0x10]
0804849B  890424            mov [esp],eax
0804849E  E8C5FEFFFF        call dword 0x8048368
080484A3  48                dec eax
080484A4  3985E4FBFFFF      cmp [ebp-0x41c],eax
080484AA  7347              jnc 0x80484f3
080484AC  81BDE4FBFFFFFB03  cmp dword [ebp-0x41c],0x3fb
         -0000
080484B6  7602              jna 0x80484ba
080484B8  EB39              jmp short 0x80484f3
080484BA  8D85E8FBFFFF      lea eax,[ebp-0x418]
080484C0  89C3              mov ebx,eax
080484C2  039DE4FBFFFF      add ebx,[ebp-0x41c]
080484C8  8B85E4FBFFFF      mov eax,[ebp-0x41c]
080484CE  0345F0            add eax,[ebp-0x10]
080484D1  8D4801            lea ecx,[eax+0x1]
080484D4  8B85E4FBFFFF      mov eax,[ebp-0x41c]
080484DA  0345F0            add eax,[ebp-0x10]
080484DD  0FB610            movzx edx,byte [eax]
080484E0  0FB601            movzx eax,byte [ecx]
080484E3  28D0              sub al,dl
080484E5  045A              add al,0x5a
080484E7  8803              mov [ebx],al
080484E9  8D85E4FBFFFF      lea eax,[ebp-0x41c]
080484EF  FF00              inc dword [eax]
080484F1  EBA5              jmp short 0x8048498
080484F3  8D85E8FBFFFF      lea eax,[ebp-0x418]
080484F9  89C2              mov edx,eax
080484FB  0395E4FBFFFF      add edx,[ebp-0x41c]
08048501  8B85E4FBFFFF      mov eax,[ebp-0x41c]
08048507  0345F0            add eax,[ebp-0x10]
0804850A  0FB600            movzx eax,byte [eax]
0804850D  C0F804            sar al,0x4
08048510  240F              and al,0xf
08048512  0421              add al,0x21
08048514  8802              mov [edx],al
08048516  8D85E9FBFFFF      lea eax,[ebp-0x417]
0804851C  89C2              mov edx,eax
0804851E  0395E4FBFFFF      add edx,[ebp-0x41c]
08048524  8B85E4FBFFFF      mov eax,[ebp-0x41c]
0804852A  0345F0            add eax,[ebp-0x10]
0804852D  0FB600            movzx eax,byte [eax]
08048530  240F              and al,0xf
08048532  0421              add al,0x21
08048534  8802              mov [edx],al
08048536  8D85EAFBFFFF      lea eax,[ebp-0x416]
0804853C  0385E4FBFFFF      add eax,[ebp-0x41c]
08048542  C60000            mov byte [eax],0x0
08048545  C785E4FBFFFF0000  mov dword [ebp-0x41c],0x0
         -0000
0804854F  8D85E8FBFFFF      lea eax,[ebp-0x418]
08048555  890424            mov [esp],eax
08048558  E80BFEFFFF        call dword 0x8048368
0804855D  48                dec eax
0804855E  3985E4FBFFFF      cmp [ebp-0x41c],eax
08048564  7205              jc 0x804856b
08048566  E99B000000        jmp dword 0x8048606
0804856B  8D85E8FBFFFF      lea eax,[ebp-0x418]
08048571  89C1              mov ecx,eax
08048573  038DE4FBFFFF      add ecx,[ebp-0x41c]
08048579  8D85E8FBFFFF      lea eax,[ebp-0x418]
0804857F  89C2              mov edx,eax
08048581  0395E4FBFFFF      add edx,[ebp-0x41c]
08048587  8D85E9FBFFFF      lea eax,[ebp-0x417]
0804858D  0385E4FBFFFF      add eax,[ebp-0x41c]
08048593  0FB600            movzx eax,byte [eax]
08048596  3202              xor al,[edx]
08048598  8801              mov [ecx],al
0804859A  8D85E9FBFFFF      lea eax,[ebp-0x417]
080485A0  89C1              mov ecx,eax
080485A2  038DE4FBFFFF      add ecx,[ebp-0x41c]
080485A8  8D85E9FBFFFF      lea eax,[ebp-0x417]
080485AE  89C2              mov edx,eax
080485B0  0395E4FBFFFF      add edx,[ebp-0x41c]
080485B6  8D85E8FBFFFF      lea eax,[ebp-0x418]
080485BC  0385E4FBFFFF      add eax,[ebp-0x41c]
080485C2  0FB600            movzx eax,byte [eax]
080485C5  3202              xor al,[edx]
080485C7  8801              mov [ecx],al
080485C9  8D85E8FBFFFF      lea eax,[ebp-0x418]
080485CF  89C1              mov ecx,eax
080485D1  038DE4FBFFFF      add ecx,[ebp-0x41c]
080485D7  8D85E8FBFFFF      lea eax,[ebp-0x418]
080485DD  89C2              mov edx,eax
080485DF  0395E4FBFFFF      add edx,[ebp-0x41c]
080485E5  8D85E9FBFFFF      lea eax,[ebp-0x417]
080485EB  0385E4FBFFFF      add eax,[ebp-0x41c]
080485F1  0FB600            movzx eax,byte [eax]
080485F4  3202              xor al,[edx]
080485F6  8801              mov [ecx],al
080485F8  8D85E4FBFFFF      lea eax,[ebp-0x41c]
080485FE  830002            add dword [eax],byte +0x2
08048601  E949FFFFFF        jmp dword 0x804854f
08048606  8D95E8FBFFFF      lea edx,[ebp-0x418]
0804860C  8B45F4            mov eax,[ebp-0xc]
0804860F  89442404          mov [esp+0x4],eax
08048613  891424            mov [esp],edx
08048616  E81DFDFFFF        call dword 0x8048338
0804861B  85C0              test eax,eax
0804861D  751A              jnz 0x8048639
0804861F  C7042492870408    mov dword [esp],0x8048792
08048626  E85DFDFFFF        call dword 0x8048388
0804862B  C704249B870408    mov dword [esp],0x804879b
08048632  E811FDFFFF        call dword 0x8048348
08048637  EB0C              jmp short 0x8048645
08048639  C70424A3870408    mov dword [esp],0x80487a3
08048640  E843FDFFFF        call dword 0x8048388
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
