void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            if(amplitude == 0){
                detect_eq_state = DEQInit;
            }
            else if(amplitude > 0){
                detect_eq_statq = eq_detected;
            }
            else{
                detect_eq_state = DEQInit;
            }
            break;
        case eq_detected:
            if(amplitude <= 0){
                detect_eq_state = DEQInit;
            }
            else{
                detect_eq_state = DEQInit;
            }
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            eq = 0x00;
            break;
        case eq_detected:
            eq = 0x02;
            break;
        default:
            break;
    }
}
