# ColdAPI_Steam

ColdAPI is a mini Steam offline emulator for Windows that allows you to play Steam games in SinglePlayer. This emulator is written in C++ and some parts of the code in Assembly.


## Features

  - steam_api(64) emulation
  - steamclient(64) emulation
  - DLC unlocking (Feature to unlock all DLCs and DLC listing too, which the format is the same as other emus).
  - Steam stub bypass (only for the newest variants)
  - Auto configuration (if you don't want to use the INI file for configuration at all, you need at least the steam_appid.txt file to provide to the emulator, the game AppId)
  - Callbacks (The callbacks might be the more harder part to code in a Steam emu for someone who have small knowlegde, however I explain the callback code line by line, so hope you can understand it.)
  - Steam_Internal exported functions.
  - RemoteStorage interface. (Game progress files save, the default directory is where you have the built dll, so steam_api(64).dll,
"ColdStorage/%your-username%/%AppId%/LocalSaves")
  - New interfaces from the sdk v146 are supprted (Not all interfaces are implemented though. That's because this project was initially started with the Open Steamworks from 2016. So don't be surprised if you see the older sdk, as this project is based from the old sdk.)

## Build requirements
- Visual Studio 2017 or higher is required
- MSVC compiler should be fine
- MASM for compiling the Assembly code
          
## Notes
- Do **NOT** use this emulator if you don't own a legit copy of the game.
    
## Credits
- [Distorm](https://github.com/gdabah/distorm) Disassembler for the hook trampoline
- [ColdHook](https://github.com/Rat431/ColdHook) for the steamclient LoadLibraries injection mode