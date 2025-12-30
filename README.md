# HFC_CH10
HFC_CH10

1. process 的檔案描述子與資料串流記錄於描述子表格(0~255)

2. ./myprog. 2>&1  把標準錯誤(2)也導向與表準輸出(1)同樣的地方

3. FILE *my_file = fopen("guitar.mp3" , "r");
   int descriptor = fileno(my_file);  回傳描述子ex:4
   ** fileno失敗時不會回傳 -1

4. dup2(4,3);  複製數據流，譬如把3號描述子重新指向4號描述子的數據流。3號將會跟4號一樣。

5. waitpid(pid ,pid_status , options)  
   pid: child process的process id
   pid_status: 這將儲存 該process的退出資訊，waitpid將更新它，因此必須是指標。
   options:可以用 man waitpid查看，設為0，函式將等待process結束。
   ex: waitpid(pid ,&pid_status ,0);

6. status（狀態），要知道child process的退出狀態，可透過 WEXITSTATUS()的巨集傳遞pid_status值。
   因pid_status只有前8個位元代表退出狀態，該巨集只告訴那8個位元值。  

7. WIFSIGNALED(pid_status) 判斷process是自然死亡，還是他殺

8. pid_status 用不同位元來儲存訊息 

9. python rssgossip.py -u 'pajama death' | grep 'http'   |代表兩個process的以管線相連接
    rssgossip.py把輸出發送到管線               grep過濾rssgossip.py指令搞的輸出
    管線是parent process (執行grep) 跟 child process (rssgossip.py)的連接

10. int fd[2];
    pipe(fd);  pipe() 函式建立管線，並回傳兩個描述子 ， fd[1] 用來向管線寫入資料，fd[0]用來從管線讀取數據
    可在parent process跟 child process使用這兩個描述子。

11. char launch[255];   開啟網頁
    sprintf(launch , "cmd /c start %s" , url);  //windows
    system(launch);
    sprintf(launch , "x-www-browser '%s' &" , url);  //linux
    system(launch);
    sprintf(launch , "open '%s'" , url);   //mac
    system(launch);

12. signal 是整數值
    sigaction 是函式包裹器，是包含指向函式之指標的struct
    sigaction所包裹的函式被稱作處理器(handler)
    struct sigaction action; 建立新動作(action)
    action.sa_handler = diediedie;  diediedie是要呼叫的函式名稱
    sigemptyset(&action.sa_mask); mask（遮罩）是過濾sigaction將處理之信號的機制
    action.sa_flags = 0;有一些額外的旗標，可以僅將它們設為0
    
    ＊＊在處理器(handler)撰寫標準輸入輸出時，務必要小心，因為某件壞事發生在程式上，所以信號會出現，並前到達處理器函式，那可能表示標準輸入輸出無效。所以一定要小心

13. sigaction(signal_no , &new_action , &old_action); sigaction 以sigaction來註冊，告訴作業系統關於它的資訊。如果失敗會回傳 -1，並且 
    設定errno變數。
    signal_no：信號數字，EX: SIGINT、SIGQUIT
    new_action：新動作
    old_action：舊動作，如果不在乎既有的處理器，可以設NULL

14. SIGINT：行程被中斷。
    SIGQUIT：有人要求行程停止，並且將記憶體傾卸在core dump檔案中。
    SIGFPE：浮點數錯誤。
    SIGTRAP：偵錯器詢問行程在哪裡。
    SIGSEGV：行程試圖存取不合法記憶體。
    SIGWINCH：終端視窗改變尺寸
    SIGTERN：有人要求核心(kernel)殺掉行程。
    SIGPIPE：行程寫入沒有東西讀取的管線。

15. kill 78222        kill可以傳送任何你想要的訊號
    kill -INT 78222
    kill -SEGV 78222
    kill -KILL 78222

16. raise() 行程傳送信號給它自己。通常用在自訂的信號處理器中，表示可以針對某次要的小事接收信號，然後選擇是否要提出更嚴重的信號。
    這被稱作信號逐步提升(signal escalation)。
    ex: raise(SIGTERM);
    
17. SIGALRM：警示信號(alarm signal)，警示信號通常是由行程的定時器(interval timer)所建立。
    alarm(120); 定時器每隔120秒觸發一次。
    警示信號讓你進行多工(multitask)處理，假如每隔幾秒就必須執行特定工作，或者如果你想要限制花在某項工作上的時間量，
    那麼警示信號就是讓程式打斷它自己的好方法。
    sleep();是讓程式睡一段時間，也算是定時器。同時使用alarm()跟sleep()會彼此互相干擾。

18. SIG_DFL：表示預設的處理器
    catch_signal(SIGTERM , SIG_DFL);

    SIG_IGN：叫行程完全忽略信號
    catch_signal(SIGTERM , SIG_IGN);

19. 信號的傳遞次數與順序是取決於作業系統平台決定，不是按程式機制。




    