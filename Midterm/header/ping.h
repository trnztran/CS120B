void Ping()
{
    switch(ping_state)
    {
        case PInit:
            ping_state = pingLow;
            break;
        case pingLow:
            ping_state = pingHigh;
            break;
        case pingHigh:
            ping_state = pingLow;
            break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
        case pingLow:
            pingB = 0x00;
            break;
        case pingHigh:
            pingB = 0x01;
            break;
        default:
            break;
    }
}
