void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
            DMA = 0;
            detect_max_amp_state = DMA2;
            break;
        case DMA2:
            DMA = amplitude;
            break;
        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            DMA = 0;
            break;
        case DMA2:
            DMA = amplitude;
            break;
        default:
            break;
    }
}
