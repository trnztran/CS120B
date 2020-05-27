void Transmit()
{
    switch(transmit_state)
    {
        case TInit:
            transmit_state = combSM;
            break;
        case combSM:
            break;
        default:
            transmit_state = TInit;
            break;
    }
    switch(transmit_state)
    {
        case TInit:
            break;
        case combSM:
            PORTB = (ping|eq|DMA);
        default:
            break;
    }

}
