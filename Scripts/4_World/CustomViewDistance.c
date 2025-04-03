class CustomViewDistance
{
    // Remove static modifier from viewDistance to make it an instance variable
    float viewDistance;

    // Define static paths to the configuration folder and file
    static const string CONFIG_FOLDER = "$profile:ViewDistance";
    static const string CONFIG_FILE = CONFIG_FOLDER + "/ViewDistanceConfig.json";

    // Constructor to load the configuration on instantiation
    void CustomViewDistance()
    {
        LoadConfig();
    }

    // Static method to initialize global settings or handle static context
    static void InitGlobals()
    {
        // Create the configuration folder and file if they do not exist
        if (!FileExist(CONFIG_FOLDER))
        {
            Print("Creating config folder at: " + CONFIG_FOLDER);
            MakeDirectory(CONFIG_FOLDER);
        }

        if (!FileExist(CONFIG_FILE))
        {
            Print("Configuration file not found. Creating a new config file at: " + CONFIG_FILE);
            CustomViewDistance newConfig = new CustomViewDistance();
            newConfig.viewDistance = 3000.0;  // Default view distance
            newConfig.SaveConfig();  // Save the config using the instance method
        }
        else
        {
            CustomViewDistance config = new CustomViewDistance();
            config.LoadConfig();  // Load the config using the instance method
        }
    }

    // Method to load configuration values
    void LoadConfig()
    {
        Print("Loading configuration from: " + CONFIG_FILE);
        JsonFileLoader<CustomViewDistance>.JsonLoadFile(CONFIG_FILE, this);  // Load into this instance
    }

    // Method to save configuration values
    void SaveConfig()
    {
        Print("Saving configuration to: " + CONFIG_FILE);
        JsonFileLoader<CustomViewDistance>.JsonSaveFile(CONFIG_FILE, this);  // Save this instance's values
    }

    // Get view distance value
    float GetViewDistance()
    {
        return viewDistance;
    }

    // Set view distance and save configuration
    void SetViewDistance(float newDistance)
    {
        viewDistance = newDistance;
        SaveConfig();
    }
}
