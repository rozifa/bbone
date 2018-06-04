// Erich Spaker Gets BTFOed Once AGAIN
int evenBitBoyz(void){
	int byte = 0x5555;
	int new = byte | byte<<16;
	return new | new<<32;
}