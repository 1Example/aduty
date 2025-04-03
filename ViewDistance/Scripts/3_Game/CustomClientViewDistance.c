class CustomClientViewDistance
{
    void CustomClientViewDistance()
    {
        GetDayZGame().Event_OnRPC.Insert(HandleViewDistanceRPC);
    }

    void ~CustomClientViewDistance()
    {
        GetDayZGame().Event_OnRPC.Remove(HandleViewDistanceRPC);
    }

    void HandleViewDistanceRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if (rpc_type == 9999)  // Ensure this matches the server RPC ID
        {
            Param1<float> viewDistanceParam;
            if (ctx.Read(viewDistanceParam))
            {
                float distance = viewDistanceParam.param1;

                // Set terrain view distance on the client
                Print("Client: Setting terrain view distance to: " + distance.ToString());
                GetGame().GetWorld().SetPreferredViewDistance(distance);

                // Set object view distance on the client
                Print("Client: Setting object view distance to: " + distance.ToString());
                GetGame().GetWorld().SetObjectViewDistance(distance);

                // Set the general view distance on the client
                Print("Client: Setting view distance to: " + distance.ToString());
                GetGame().GetWorld().SetViewDistance(distance);

                // Additional confirmation message for debugging
                Print("Client: All available view distances successfully set to " + distance.ToString());
            }
        }
    }
}
