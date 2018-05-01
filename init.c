#include "Missions\dayzOffline.ChernarusPlus\CustomLifeSpanOverride.c"

ref TVectorArray positions = {"15135.1 0 13901.1", "15017.8 0 13892.4", "14887.1 0 14547.9", "14749.7 0 13248.7", "14697.6 0 13418.4", "14537.3 0 14755.7", "14415.3 0 14025.2", "14338.0 0 12859.5", "14263.8 0 12748.7", "14172.2 0 12304.9", "14071.4 0 12033.3", "14054.9 0 11341.3", "14017.8 0 2959.1", "13905.5 0 12489.7", "13852.4 0 11686.0", "13846.6 0 12050.0", "13676.0 0 12262.1", "13617.4 0 12759.8", "13610.1 0 11223.6", "13594.3 0 4064.0", "13587.8 0 6026.5", "13571.1 0 3056.8", "13552.6 0 4653.7", "13529.9 0 3968.3", "13520.8 0 4223.7", "13504.0 0 5004.5", "13476.7 0 6136.3", "13441.6 0 5262.2", "13426.6 0 5747.3", "13416.8 0 11840.4", "13400.8 0 4120.7", "13395.8 0 5902.8", "13385.0 0 3946.6", "13374.4 0 6454.3", "13367.1 0 10837.1", "13366.3 0 4906.0", "13337.1 0 5120.8", "13326.7 0 5489.1", "13312.7 0 6771.1", "13288.7 0 11415.1", "13261.6 0 11785.2", "13171.6 0 6534.8", "13159.8 0 5401.7", "13155.2 0 5475.2", "13138.8 0 6737.3", "13112.3 0 11280.7", "13111.7 0 10975.5", "13101.2 0 7657.3", "13099.1 0 6393.0", "13084.9 0 7938.6", "13056.8 0 4848.5", "13048.1 0 8357.6", "13048.1 0 3867.7", "12991.7 0 7287.1", "12983.0 0 5539.1", "12978.9 0 9727.8", "12950.2 0 5226.7", "12942.1 0 8393.1", "12891.5 0 3673.9", "12628.7 0 10495.2", "12574.3 0 3592.8", "12566.3 0 6682.6", "12465.2 0 8009.0", "12354.5 0 3480.0", "13262.8 0 7225.8", "13170.0 0 7406.3", "12936.7 0 10734.0", "12929.7 0 8578.3", "12917.3 0 9356.6", "12889.9 0 8792.8", "12868.7 0 9054.5", "12800.7 0 10542.7", "12796.3 0 10361.3", "12789.2 0 10918.7", "12774.0 0 7792.6", "12729.8 0 11285.5", "12689.8 0 8256.0", "12651.2 0 8914.4", "12614.7 0 7304.6", "12343.6 0 10169.8", "12332.0 0 8170.0", "12221.6 0 8693.6", "12135.7 0 10209.8", "11914.3 0 3402.0", "11846.8 0 3477.8", "11709.4 0 3388.2", "11578.0 0 3159.0", "11439.0 0 3315.2", "11201.5 0 3186.6", "11075.8 0 3031.2", "11049.3 0 2801.6", "10969.2 0 2895.1", "10875.8 0 2518.9", "10820.4 0 2257.4", "10757.4 0 2662.2", "10294.2 0 2822.9", "10032.8 0 2446.5", "9823.2 0 2712.6", "9691.7 0 1750.4", "9529.7 0 1791.2", "9479.7 0 2373.5", "9193.7 0 1935.7"};

ref TStringArray tops = {"Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red"};
ref TStringArray pants = {"Jeans_Black","Jeans_BlueDark","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey"};
ref TStringArray shoes = {"AthleticShoes_Black","AthleticShoes_Blue","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey"};

bool inited = false;

ref CustomPluginLifespan lifespanp;
ref PlayerBase oPlayer;

string playersave = "$profile:\\player.txt";

bool extendedLoadout = false;

int keybindtimeout = 0;
int savetimeout = 0;

void main()
{
  init();
  if(inited) {
    update();
  }
}

void init() {
  g_Game.SetMissionState( DayZGame.MISSION_STATE_GAME );
  lifespanp = new CustomPluginLifespan();
  spawnPlayer();
  startHive();
  setWeatherLimits();
  g_Game.m_loadingScreenOn = false;
  inited = true;
}

//main mission loop
void update() {
  int sleeptime = 200;
  int keydelay = 500; //ms between keypresses, default half a second.
  int savedelay = 2000; //ms between saves, default 2 seconds.
  while(true) {
    if(oPlayer) {
      int life_state = oPlayer.GetPlayerState();
      if (life_state != EPlayerStates.DEAD) {
        if(savetimeout >= savedelay) {
          savePlayerToFile();
        }
    	}
      else {
        if(FileExist(playersave)) {
          DeleteFile(playersave);
        }
      }
      oPlayer.StatUpdateByTime("playtime");
      lifespanp.UpdateLifespan( oPlayer, true );
  		lifespanp.UpdateBloodyHandsVisibility(oPlayer, oPlayer.HasBloodyHands());
      if(keybindtimeout >= keydelay) {
        handleInput();
      }
    }
  if(keybindtimeout <= keydelay) {
    keybindtimeout+=sleeptime;
  }
  if(savetimeout <= savedelay) {
    savetimeout+=sleeptime;
  }
  Sleep(sleeptime);
  }
}

void handleInput() {
  if(KeyState(KeyCode.KC_P) && KeyState(KeyCode.KC_LSHIFT)) {
    if(FileExist(playersave) && oPlayer) {
      DeleteFile(playersave);
      GetGame().RestartMission();
      keybindtimeout = 0;
    }
  }
  if(KeyState(KeyCode.KC_B) && KeyState(KeyCode.KC_LSHIFT)) {
    ItemBase handitem = oPlayer.GetHumanInventory().GetEntityInHands();
    string handitemtype = handitem.GetType();
    handitemtype.ToLower();
    if(handitemtype.IndexOf("knife") != -1) {
      oPlayer.ShavePlayer();
      oPlayer.MessageStatus("Nothing better than a clean shave!");
    }
    else {
      oPlayer.MessageStatus("I need to have a knife in my hands to shave!");
    }
    keybindtimeout = 0;
  }
}

void spawnPlayer() {
  if(FileExist(playersave)) {
    spawnPlayerFromFile();
  } else {
    spawnFreshPlayer();
  }
  GetGame().SelectPlayer(NULL, oPlayer);
}

void spawnPlayerFromFile() {
  FileHandle file = OpenFile(playersave, FileMode.READ);
  //FileHandle file = OpenFile("$CurrentDir:\\oPlayer.log", FileMode.WRITE);

  string line = "4603.797363 342.474487 10492.90722";

  FGets(file,  line);
  vector position = line.ToVector();

  FGets(file,  line);
  vector direction = line.ToVector();

  string overcast, rain, fog, wind;
  FGets(file,  overcast); FGets(file,  rain); FGets(file,  fog); FGets(file,  wind);

  Weather weather = g_Game.GetWeather();
  weather.GetOvercast().Set(overcast.ToFloat());
  weather.GetRain().Set(rain.ToFloat());
  weather.GetFog().Set(fog.ToFloat());
  weather.SetWindSpeed(wind.ToFloat());

  string sorigYear, sorigMonth, sorigDay, sorigHour, sorigMinute;
  FGets(file,  sorigYear); FGets(file,  sorigMonth); FGets(file,  sorigDay); FGets(file,  sorigHour); FGets(file,  sorigMinute);

  int origYear, origMonth, origDay, origHour, origMinute;
  GetGame().GetWorld().GetDate( origYear, origMonth, origDay, origHour, origMinute );

  TStringArray inventoryItems = new TStringArray;
  while(FGets(file,  line) > 0 && line  != "END_ITEMS") {
    inventoryItems.Insert(line);
  }

  string inHands = "";

  FGets(file, line);
  string modelType = line;
  if(line == "IN_HANDS") {
    FGets(file, inHands);
    FGets(file, modelType);
  }
  //FGets(file,  line);



  string shealth, sblood, stemp, senergy, swater;
  FGets(file, shealth); FGets(file, sblood); FGets(file, stemp); FGets(file, senergy); FGets(file, swater);

  string splaytime, slastshave, sbloodyhands;
  FGets(file, splaytime); FGets(file, slastshave); FGets(file, sbloodyhands);

  string stimepassed;
  FGets(file, stimepassed);
  GetGame().GetWorld().SetDate( sorigYear.ToInt(), sorigMonth.ToInt(), sorigDay.ToInt(), sorigHour.ToInt() + (stimepassed.ToInt() / (60*60)), sorigMinute.ToInt() + (stimepassed.ToInt() / 60) );

  CloseFile(file);

  Print("Creating player with type: " + modelType);
  //Create oPlayer object
  oPlayer = PlayerBase.Cast( GetGame().CreatePlayer( NULL, modelType, "0 0 0", 0, "NONE") );
  oPlayer.StatRegister("playtime");

  //set position and direction
  oPlayer.SetPosition( position );
  oPlayer.SetDirection( direction );

  //playtime, beard, bloody hands

  oPlayer.StatUpdate("playtime", splaytime.ToFloat());
  oPlayer.SetLastShavedSeconds(slastshave.ToFloat());
  if(sbloodyhands == "true") {
    oPlayer.SetBloodyHands(true);
  } else {
    oPlayer.SetBloodyHands(false);
  }

  lifespanp.UpdateLifespan( oPlayer, true );
  oPlayer.SetSynchDirty();

  //Add items
  ItemBase handItem;
  if(inHands != "") {
    handItem = oPlayer.GetInventory().CreateInInventory(inHands);
    //oPlayer.PredictiveTakeEntityToHands(handItem);
    if(handItem == NULL) {
         g_Game.CreateObject( inHands, g_Game.GetPlayer().GetPosition(), false );
    }
  }

  for(int i=0; i<inventoryItems.Count(); i++) {
    if(oPlayer.GetInventory().CreateInInventory(inventoryItems[i]) == NULL) { //if space in inventory for item, spawn in inventory
      //try to attack to hand weapon
      if(handItem != NULL && handItem.GetInventory().CreateAttachment(inventoryItems[i]) == NULL) {
        //spawn on ground
        g_Game.CreateObject( inventoryItems[i], g_Game.GetPlayer().GetPosition(), false );
      }
    }
  }

  oPlayer.SetHealth("","", shealth.ToFloat());
  oPlayer.SetHealth("GlobalHealth", "Blood", sblood.ToFloat());
  oPlayer.GetStatTemperature().Set(stemp.ToFloat());
  oPlayer.GetStatEnergy().Set(senergy.ToFloat());
  oPlayer.GetStatWater().Set(swater.ToFloat());
}

void spawnFreshPlayer() {
  vector player_pos;
  int index;

  index = Math.RandomInt(0, positions.Count() );

  player_pos = positions.Get(index);
  Print(player_pos);
  Entity playerEnt = GetGame().CreatePlayer( NULL, GetGame().CreateRandomPlayer(), player_pos, 0, "NONE");

  oPlayer = (PlayerBase) playerEnt;
  oPlayer.StatRegister("playtime");

  EntityAI item = oPlayer.GetInventory().CreateInInventory(tops.GetRandomElement());
  EntityAI item2 = oPlayer.GetInventory().CreateInInventory(pants.GetRandomElement());
  EntityAI item3 = oPlayer.GetInventory().CreateInInventory(shoes.GetRandomElement());

  EntityAI itemEnt;
  EntityAI itemIn;
  ItemBase itemBs;
  int rndQnt;

  itemEnt = oPlayer.GetInventory().CreateInInventory("Rag");
  itemBs = ItemBase.Cast(itemEnt);
  itemBs.SetQuantity(4);
  SetRandomHealth(itemEnt);

  if(extendedLoadout) {
    itemEnt = oPlayer.GetInventory().CreateInInventory("Mag_IJ70_8Rnd");
    SetRandomHealth(itemEnt);

    itemEnt = oPlayer.GetInventory().CreateInInventory("HuntingKnife");
    SetRandomHealth(itemEnt);

    itemEnt = oPlayer.GetInventory().CreateInInventory("MakarovIJ70");
    SetRandomHealth(itemEnt);
    oPlayer.SetQuickBarEntityShortcut(itemEnt, 2);

    itemIn = itemEnt.GetInventory().CreateAttachment("Mag_IJ70_8Rnd");
    SetRandomHealth(itemIn);

    itemEnt = oPlayer.GetInventory().CreateInInventory("Izh18");
    SetRandomHealth(itemEnt);
    oPlayer.SetQuickBarEntityShortcut(itemEnt, 0);

    itemBs = ItemBase.Cast(itemEnt);
    itemBs.SetQuantity(rndQnt);

    itemEnt = oPlayer.GetInventory().CreateInInventory("Ammo_762x39");
    rndQnt = Math.RandomInt(5,20);
    SetRandomHealth(itemEnt);
    oPlayer.SetQuickBarEntityShortcut(itemEnt, 1);

    itemEnt = oPlayer.GetInventory().CreateInInventory("Ammo_380");
    SetRandomHealth(itemEnt);
  }
}

void setWeatherLimits() {
  Weather weather = g_Game.GetWeather();
  weather.GetOvercast().SetLimits( 0.0 , 1.0 );
  weather.GetRain().SetLimits( 0.0 , 1.0 );
  weather.GetFog().SetLimits( 0.0 , 0.5 );

  weather.GetOvercast().SetForecastChangeLimits( 0.0, 0.3);
  weather.GetRain().SetForecastChangeLimits( 0.0, 0.3 );
  weather.GetFog().SetForecastChangeLimits( 0.0, 0.3 );

  weather.GetOvercast().SetForecastTimeLimits( 800 , 1800 );
  weather.GetRain().SetForecastTimeLimits( 600 , 1200 );
  weather.GetFog().SetForecastTimeLimits( 600 , 1200 );

  weather.SetWindMaximumSpeed(5);
  weather.SetWindFunctionParams(0.2, 1.0, 50);
}

void startHive() {
  Hive myHive = CreateHive();
  if( myHive )
  {
    myHive.InitOffline();
  }
}

void savePlayerToFile() {
	FileHandle file = OpenFile(playersave, FileMode.WRITE);
	//FileHandle file = OpenFile("$CurrentDir:\\oPlayer.log", FileMode.WRITE);

	FPrintln(file, oPlayer.GetPosition());
	FPrintln(file, oPlayer.GetDirection());

	Weather weather = g_Game.GetWeather();


	int origYear, origMonth, origDay, origHour, origMinute;
	GetGame().GetWorld().GetDate( origYear, origMonth, origDay, origHour, origMinute );

	string overcast = weather.GetOvercast().GetActual().ToString();
	string rain = weather.GetRain().GetActual().ToString();
	string fog = weather.GetFog().GetActual().ToString();
	string wind = weather.GetWindSpeed().ToString();
	FPrintln(file, overcast);
	FPrintln(file, rain);
	FPrintln(file, fog);
	FPrintln(file, wind);
	FPrintln(file, origYear.ToString());
	FPrintln(file, origMonth.ToString());
	FPrintln(file, origDay.ToString());
	FPrintln(file, origHour.ToString());
	FPrintln(file, origMinute.ToString());

	array<EntityAI> itemsArray = new array<EntityAI>;
	ItemBase item;
	oPlayer.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);

	ItemBase inHands = oPlayer.GetHumanInventory().GetEntityInHands();
	for (int i = 0; i < itemsArray.Count(); i++)
	{
		Class.CastTo(item, itemsArray.Get(i));
		if (item && !item.IsInherited(SurvivorBase) && item != inHands) {
			FPrintln(file, item.GetType());
		}
	}

	FPrintln(file, "END_ITEMS");
	if(inHands) {
		FPrintln(file, "IN_HANDS");
    FPrintln(file, inHands.GetType());
	}


	string modelname = oPlayer.GetType();
	FPrintln(file, modelname);

	//.SetHealth( "", "", old_item.GetHealth("", "") );
	float health =  oPlayer.GetHealth("", "");
	float blood = oPlayer.GetHealth("GlobalHealth", "Blood");
	float temperature = oPlayer.GetStatTemperature().Get();
	float energy = oPlayer.GetStatEnergy().Get();
	float water = oPlayer.GetStatWater().Get();


	FPrintln(file, health);
	FPrintln(file, blood);
	FPrintln(file, temperature);
	FPrintln(file, energy);
	FPrintln(file, water);

	//playtime and beard
	float playtime = oPlayer.StatGet("playtime");
	float beard = oPlayer.GetLastShavedSeconds();
	bool hasBloodyHands = oPlayer.HasBloodyHands();

	FPrintln(file, playtime);
	FPrintln(file, beard);
	FPrintln(file, hasBloodyHands.ToString());

	float timepassed = weather.GetTime();
	FPrintln(file, timepassed);

	CloseFile(file);
  savetimeout = 0;
}

void SetRandomHealth(EntityAI itm)
{
	int rndHlt = Math.RandomInt(40,100);
	itm.SetHealth("","",rndHlt);
}
