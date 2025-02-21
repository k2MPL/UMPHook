# UMPHook


![logo](https://github.com/user-attachments/assets/b72d2c98-c69a-4f97-811b-0c3dcaebf00b)


<ins>Ultimate Spider-Man modpack hook</ins>: DLL that replace original binkw32.dll that USM game is using to inject custom code in game process. Original binkw32.dll should be near exe but renamed to binkw32_.dll 
(Custom build events will take care of that. You don't need to make such preperations by yourself. Check 'post build events' tab to see how working environment automatically prepared)

##

> [!CAUTION]
> - Before you get started it's highly recommended to create backup for following files: USM.exe, binkw32.dll
> - ASLR (Address Space Layout Randomization) must be disabled!
>
> ![image](https://github.com/user-attachments/assets/5cf1818e-c3c5-471f-bd62-f989d1562405)

## 

Setup:
- Create environment variable USM_PATH that indicates path to root folder where game is installed (example: C:\Ultimate Spider-Man)
- Open solution. Build & Run
