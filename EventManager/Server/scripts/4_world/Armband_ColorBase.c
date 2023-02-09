modded class Armband_ColorBase
{
    override void OnWasAttached( EntityAI parent, int slot_id )
	{
		super.OnWasAttached(parent, slot_id);
		
		PlayerBase player = PlayerBase.Cast(parent);
		if (player)
		{
			if ( !GetGame().IsServer() )
				return;
            //lets remove from none if needed
			if (GetSimpleEventManager())
			{
				if (GetSimpleEventManager().HasPlayerInGroup("none", player))
					GetSimpleEventManager().RemovePlayer(player);
				GetSimpleEventManager().AddPlayer(player);
			}
		}
	}
	
	override void OnWasDetached( EntityAI parent, int slot_id )
	{
		super.OnWasDetached(parent, slot_id);
		
		PlayerBase player = PlayerBase.Cast(parent);
		if (player)
		{
			if ( !GetGame().IsServer() )
				return;
            GetSimpleEventManager().RemovePlayer(player);
		}
	}
}