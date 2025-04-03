modded class MissionServer
{
    protected ref CustomViewDistance m_CustomViewDistance;

    void MissionServer()
    {
        // Initialize static globals for view distance configuration
        CustomViewDistance.InitGlobals();

        // Create an instance of CustomViewDistance
        m_CustomViewDistance = new CustomViewDistance();
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        ChatMessageEventParams chatParams = ChatMessageEventParams.Cast(params);
        if (eventTypeId == ChatMessageEventTypeID && chatParams)
        {
            string chatText = chatParams.param3;

            // Check if the message is the command to set view distance
            if (chatText.IndexOf("!setviewdistance") == 0)
            {
                TStringArray tokens = new TStringArray;
                chatText.Split(" ", tokens);

                if (tokens.Count() >= 2)
                {
                    float distance = tokens[1].ToFloat();
                    if (distance > 0)
                    {
                        // Set the view distance using the setter method
                        m_CustomViewDistance.SetViewDistance(distance);
                        SetViewDistanceForAllPlayers(distance);

                        // Send message to admin or player who issued command
                        SendMessageToAdmins("View distance set to: " + distance.ToString());
                    }
                    else
                    {
                        SendMessageToAdmins("Invalid distance value!");
                    }
                }
            }
        }
    }

    void SetViewDistanceForAllPlayers(float distance)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        // Set the view distance for the server environment
        GetGame().GetWorld().SetPreferredViewDistance(distance);

        for (int i = 0; i < players.Count(); i++)
        {
            Man player = players.Get(i);
            if (player)
            {
                SetPlayerViewDistance(player, distance);
            }
        }
    }

    void SetPlayerViewDistance(Man player, float distance)
    {
        PlayerBase playerBase = PlayerBase.Cast(player);
        if (playerBase && playerBase.GetIdentity())
        {
            // Send the desired view distance to the client via RPC
            Param1<float> viewDistanceParam = new Param1<float>(distance);
            GetGame().RPCSingleParam(playerBase, 9999, viewDistanceParam, true, playerBase.GetIdentity());

            // Apply view distance settings on the server side for both terrain and objects
            Print("Server: Setting preferred view distance to: " + distance.ToString());
            GetGame().GetWorld().SetPreferredViewDistance(distance);

            Print("Server: Setting object view distance to: " + distance.ToString());
            GetGame().GetWorld().SetViewDistance(distance);
        }
    }


    override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
    {
        super.OnClientReadyEvent(identity, player);
        SetPlayerViewDistance(player, m_CustomViewDistance.GetViewDistance());
    }

    void SendMessageToAdmins(string message)
    {
        array<Man> players = new array<Man>();
        GetGame().GetPlayers(players);

        for (int i = 0; i < players.Count(); i++)
        {
            Man player = players.Get(i);
            if (player && IsPlayerAdmin(player))
            {
                PlayerIdentity identity = player.GetIdentity();
                if (identity)
                {
                    GetGame().AdminLog(message);
                }
            }
        }
    }

    bool IsPlayerAdmin(Man player)
    {
        return true;
    }
}
