# DayZPersistentSP
Mod for the 0.63 Singleplayer mode that saves characters.

Hello!

Reddit Thread: https://www.reddit.com/r/dayz/comments/8ftcs2/063_persistent_singleplayer_mod_update_10_save/

Everything related to saving characters has now been moved to the init.c file (instead of the independant scripts folder).
It is now a lot cleaner to read and no need for thousands of lines of code in the scritps folder that the Mission script module dependend on.

This should bring a much cleaner, more stable, future-proof build. There is also less work involved with switching to Multiplayer if there is an online stress test happening. (after removing "scripts" folder, you don't need to do anything)

# Installation instructions:

1. Download this repository as a .zip file. Green button, top right. (or clone it directly to your mission folder if you want.)

2. **[IF YOU HAVE ANY OLDER VERSION OF MY MOD, FROM REDDIT]** Delete the "scripts" folder in your DayZ folder entirely. There is no need for it anymore. **I repeat, there should be no folder called "scripts" in your DayZ installation folder. At all.**

3. Place the "init.c" and "CustomLifeSpanOverride.c" files inside "[DayZ install folder]/Missions/dayzOffline.ChernarusPlus/". Overwrite init.c.

4. Run DayZ from Steam with the "Play DayZ Offline" option.

# Keybinds:

**SHIFT+B:** Shave your beard. You need to have a knife in your hand.

**SHIFT+P:** Deletes save file and respawn. (automatically reloads the mission).

**[Below keybinds only work if you have hacksOn set to true, see Settings below]**

**ALT+B:** Grow your beard.

**T:** Teleport to cursor.

**END:** Godmode and infinite ammo.

**O:** Spawn zombie.

**SHIFT+O:** Spawn wolf.

**SHIFT+O:** Spawn animal.

**INSERT:** Free camera.

**DELETE:** Open editor menu. Not fully working yet. (spawning items is broken).

# Settings:

In the init.c file there are a few variables you can customize:

**extendedLoadout:** if this is set to *true* you will spawn with the default offline mode gear. (IZH, Makarov, knife etc.). If this is set to *false* you will spawn with a hoodie, pants and 4 rags. 

**sleepdelay:** Time (in ms) between mission updates. This might be a good idea to set to a higher value if you are having FPS problems.

**hacksOn:** Turn on hacks. See keybinds.

# Beards:

You heard correct, beards are in this build! As of right now it takes 30 minutes for half beardness, 60 minutes for a full beard.

# Known issues:

1. Some ambient sounds dissappear after restarting mission. Restart the game completely to fix.

2. Some items may spawn in the wrong slot. (Or on the ground, always check the ground below you when you spawn in)

3. Magazine ammo counters and item quantities do not save. They will always be set to max when spawning in.

4. Admin menu not working completely. If you want to use it stick to the old version of this mod or use Arkensor's offline mod.


# Troubleshooting:

**Light blue screen when starting the game:** Run the "resetsave.bat" file from the download.

**Script or compile errors:** Remove "init.c" and perform a Steam intengrity check on your game. (DayZ->Properties->Local files->Verify local game cache). Might have to click it twice to get the right tool. (Do not trust the custom "DayZ cleanup tool", make sure you run the actual Steam verifier). Then follow the install instructions again.

# Credits:

**Arkensor** for hack options: https://github.com/Arkensor/DayZCommunityOfflineMode
