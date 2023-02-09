class PlayerGroups
{
    string group;
    array<PlayerBase> players;
};

[CF_RegisterModule(SimpleEventManager)]
class SimpleEventManager: CF_ModuleWorld
{
    // this is just for player checks and other functions
    //autoptr SimpleEventConfig config;

    //autoptr array<PlayerBase> m_players;
    //autoptr array<autoptr PlayerGroups> m_groups = new array<autoptr PlayerGroups>();
    autoptr map<string, autoptr array<PlayerBase>> m_groups = new map<string, autoptr array<PlayerBase>>();
    autoptr array<autoptr Town> scara_Towns = Town.GetMapTowns(TownFlags.CAPITAL | TownFlags.CITY | TownFlags.VILLAGE | TownFlags.CAMP | TownFlags.LOCAL);

    override void OnInit()
    {
        super.OnInit();

        // Enable the 'OnInvokeConnect' event
        EnableMissionStart();
        EnableInvokeConnect();
        EnableInvokeDisconnect();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        CF_Log.Info("[SimpleEventManager] Loading....");
    }

    override void OnInvokeConnect(Class sender, CF_EventArgs args)
    {
        super.OnInvokeConnect(sender, args);

        auto player = CF_EventPlayerArgs.Cast(args).Player;

        if( player ) AddPlayer(player);
    }

    override void OnInvokeDisconnect(Class sender, CF_EventArgs args)
    {
        super.OnInvokeDisconnect(sender, args);

        auto player = CF_EventPlayerArgs.Cast(args).Player;

        if( player ) RemovePlayer(player);
    }

    bool HasPlayerInGroup(string group, PlayerBase player, autoptr map<string, autoptr array<PlayerBase>> groups=m_groups)
    {
        if(groups && groups.Count() > 0)
        {
            foreach(string key, array<PlayerBase> players: groups)
            {
                if (players.Find(player) != -1)
                    return true;
            }
        }
        return false;
    }

    void AddPlayerToGroup(string group, PlayerBase player, autoptr map<string, autoptr array<PlayerBase>> groups=m_groups)
    {
        if (player)
        {
            if (!groups.Contains(group))
            {
                PrintFormat("[SimpleEventManager] creating %1", group);
                groups.Insert(group, new array<PlayerBase>);
            }
            
            if (groups.Contains(group))
            {
                for(int i = 0; i < groups.Count();i++)
                {
                    if (groups.GetKey(i) == group)
                    {
                        array<PlayerBase> temp = groups.GetElement(i);
                        if (!temp)
                            temp = new array<PlayerBase>();
                        temp.Insert(player);
                        groups.Set(group, temp);
                        PrintFormat("[SimpleEventManager] adding %1 to %2", player.GetIdentity().GetPlainId(), group);
                    }
                }
            }
        }
    }

    bool RemovePlayerFromGroup(string group, PlayerBase player)
    {
        if(player)
        {
            // look for player
            if (m_groups.Contains(group))
            {
                array<PlayerBase> t = m_groups.Get(group);
                int index = t.Find(player);
    
                if (index != -1 && t.Count() != 0)
                {
                    m_groups.Get(group).Remove(index);
                    PrintFormat("[SimpleEventManager] remove %1 from %2", player.GetIdentity().GetPlainId(), group);
                    return true;
                }
            }
        }
        return false;
    }

    void AddPlayer(PlayerBase player)
    {
        Print("[SimpleEventManager] Adding Player...");
        if (player)
        {
            ItemBase groupID = ItemBase.Cast(player.FindAttachmentBySlotName( "Armband" ));
            if (groupID)
                AddPlayerToGroup(groupID.GetType(), player, m_groups);
            else
                AddPlayerToGroup("none", player, m_groups);
        }
    }

    bool RemovePlayer(PlayerBase player)
    {
        Print("[SimpleEventManager] Removing Player...");
        if(player)
            foreach(string group, array<PlayerBase> players: m_groups)
                if (HasPlayerInGroup(group, player))
                    return RemovePlayerFromGroup(group, player);
        return false;
    }

    bool IsPlayerNearby(Object obj, float distance, out autoptr map<string, autoptr array<PlayerBase>> nearbyGroups=NULL)
    {
        PrintFormat("[SimpleEventManager] Checking if player nearby %1...", obj.GetType());
        vector obj_dis = obj.GetPosition();
        if (m_groups.Count() > 0)
        {
            Print("[SimpleEventManager] Checking Groups...");
            for ( int i = 0; i < m_groups.Count(); ++i )
		    {
                string key = m_groups.GetKey( i );
                PrintFormat("[SimpleEventManager] %1 - %2...", i, key);
                array<PlayerBase> value = m_groups.GetElement( i );
                if(value)
                {
                    PrintFormat("[SimpleEventManager] Has Value...");
                    foreach(PlayerBase plr: value)
                    {
                        float distance_to_player = vector.Distance(plr.GetPosition(), obj_dis);
                        PrintFormat("[SimpleEventManager] %1 %2...", plr.GetIdentity().GetPlainId(), distance_to_player);
                        if (distance_to_player <= distance)
                        {
                            if (nearbyGroups && !HasPlayerInGroup(key, plr, nearbyGroups))
                                AddPlayerToGroup(key, plr, nearbyGroups);
                            else
                                return true;
                        }
                    }
                }
            }
        }

        return false;//GetCEApi().AvoidPlayer(obj_dis, distance);
    }

    void SendNotification(autoptr StringLocaliser title, autoptr StringLocaliser text, string icon, int color, float time = 3, PlayerIdentity sendTo = NULL )
    {
        NotificationSystem.Create(title, text, icon, color, time, sendTo);
    }

    // these will be handled by Dab's Framework for ease
    void RegisterEvent(typename event_type, float freq, int min=550, int max=3500, int count=2)
    {
        EventManager.GetInstance().RegisterEvent(event_type, freq);
        EventManager.GetInstance().Run(min, max, count);
    }

    void StartEvent(typename event_type)
    {
        EventManager.GetInstance().StartEvent(event_type);
    }

    string FindClosestTown(vector position)
    {
        Town closest;
        if (scara_Towns)
            foreach(Town town: scara_Towns)
                if (!closest || vector.Distance(position, town.Position) < vector.Distance(position, closest.Position))
                    closest = town;
        if (closest)
            return closest.Name;
        return position.ToString(false);
    }
}

static autoptr SimpleEventManager m_SimpleEventManager;
static SimpleEventManager GetSimpleEventManager()
{
	if ( !m_SimpleEventManager )
		m_SimpleEventManager = new SimpleEventManager;
	return m_SimpleEventManager;
}