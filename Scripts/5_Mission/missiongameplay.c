modded class MissionGameplay
{
    ref CustomClientViewDistance m_CustomClientViewDistance;

    override void OnInit()
    {
        super.OnInit();  // Call the OnInit method of the base class
        m_CustomClientViewDistance = new CustomClientViewDistance();
    }
}
