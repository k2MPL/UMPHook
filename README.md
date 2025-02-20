# UMPHook

DLL that replace original binkw32.dll that USM game is using to inject custom code in game process. Original binkw32.dll should be near exe but renamed to binkw32_.dll 
(Custom build events will take care of that. You don't need to make such preperations by yourself. Check 'post build events' tab to see how working environment automatically prepared)

> [!CAUTION]
> - Before you get started it's highly recommended to create backup for following files: USM.exe, binkw32.dll
> - ASLR (Address Space Layout Randomization) must be disabled!
>
> ![image](https://github.com/user-attachments/assets/5cf1818e-c3c5-471f-bd62-f989d1562405)

Setup:
- Create environment variable USM_PATH that indicates path to root folder where game is installed (example: C:\Ultimate Spider-Man)
- Open solution. Build & Run

Project configuration details (JFYI, no need to take these actions by yourself. Everything is already configured):

![cfg_1](https://github.com/user-attachments/assets/b95ba562-e269-475b-939a-6ea350bfce34)
![cfg_2](https://github.com/user-attachments/assets/d279651a-2c20-4296-b316-84bd1629ee1b)
![cfg_3](https://github.com/user-attachments/assets/e68b39df-2bd8-4e10-8273-7934ebe4e936)
![cfg_4](https://github.com/user-attachments/assets/e67c429d-6462-4fb5-811a-23687ac3e621)
![cfg_5](https://github.com/user-attachments/assets/03f61870-61cb-4561-9acb-d360d6c98194)
