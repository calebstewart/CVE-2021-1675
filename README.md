# CVE-2021-1675 - PrintNightmare LPE (PowerShell)

> Caleb Stewart | John Hammond | June 1, 2021

----------------------------------------------------------

[CVE-2021-1675](https://msrc.microsoft.com/update-guide/en-US/vulnerability/CVE-2021-1675) is a critical remote code execution and local privilege escalation vulnerability dubbed "PrintNightmare."

Proof-of-concept exploits have been released ([Python](https://github.com/cube0x0/CVE-2021-1675/blob/main/CVE-2021-1675.py), [C++](https://github.com/afwu/PrintNightmare/blob/main/EXP/POC/POC.cpp)) for the remote code execution capability, and a [C# rendition](https://github.com/cube0x0/CVE-2021-1675/tree/main/SharpPrintNightmare) for local privilege escalation. We had not seen a native implementation in pure PowerShell, and we wanted to try our hand at refining and recrafting the exploit.

This PowerShell script performs local privilege escalation (LPE) with the PrintNightmare attack technique.

![image](https://user-images.githubusercontent.com/6288722/124203761-70b36580-daab-11eb-8520-7d93743062af.png)

This has been tested on Windows Server 2016 and Windows Server 2019.

## Usage

Add a new user to the local administrators group by default:

```shell
Import-Module .\cve-2021-1675.ps1
Invoke-Nightmare # add user `adm1n`/`P@ssw0rd` in the local admin group by default

Invoke-Nightmare -DriverName "Xerox" -NewUser "john" -NewPassword "SuperSecure" 
```

Supply a custom DLL payload, to do anything else you might like.

```shell
Import-Module .\cve-2021-1675.ps1
Invoke-Nightmare -DLL "C:\absolute\path\to\your\bindshell.dll"
```

## Details

* The LPE technique does not need to work with remote RPC or SMB, as it is only working with the functions of Print Spooler.
* This script embeds a Base64-encoded GZIPped payload for a custom DLL, that is patched according to your arguments, to easily add a new user to the local administrators group.
* This script embeds methods from PowerSploit/[PowerUp](https://github.com/PowerShellMafia/PowerSploit/blob/master/Privesc/PowerUp.ps1) to reflectively access the Win32 APIs.
* This method does not loop through all printer drivers to find the appropriate DLL path -- it simply grabs the first driver and determines the appropriate path.
