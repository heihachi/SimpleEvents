/*class SimpleEventConfig: Managed
{
    protected bool debug = false;
    const static string ModProfileFolder = "$profile:SimpleEventManager";
    const static string FileName = "/events.json";
    const static string ConfigPath = ModProfileFolder + FileName;

    void SimpleEventConfig()
    {
        Load();
    }

    void CreateConfig()
    {
	    if (!GetGame().IsServer()) return;

		if (!FileExist(ModProfileFolder))
        {
            Print("[SimpleEventManager] '" + ModProfileFolder + "' does NOT exist, creating directory!");
            MakeDirectory(ModProfileFolder);
        }

        if (!FileExist(ConfigPath))
        {
            Print("[SimpleEventManager] '" + ConfigPath + "' does NOT exist, creating default config!");
            Default();
        }
        LoadConfig();
    }

    bool LoadConfig()
    {
        if (FileExist(ConfigPath))
        {
            // Print("[SimpleEventConfig] '" + ConfigPath + "' found, loading existing config!");
            JsonFileLoader<SimpleEventConfig>.JsonLoadFile(ConfigPath, this);
            return true;
        }
        return false;
    }

	void Load()
    {
        CreateConfig();
        LoadConfig();
    }

	protected void Save()
    {
        JsonFileLoader<SimpleEventConfig>.JsonSaveFile(ConfigPath, this);
    }

	protected void Default()
    {
		Save();
	}

    bool Debugging() { return debug; }
};*/