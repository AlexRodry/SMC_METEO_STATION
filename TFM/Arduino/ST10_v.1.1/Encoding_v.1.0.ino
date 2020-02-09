String _SerialTelegram;

String encodeTelegram(){
  _SerialTelegram = "nombre"+Sep+St+Sep+ "Fecha"+Sep+fecha+Sep; 
  for (int i=0; i<=6; i++){
    _SerialTelegram += ids[i]+Sep+sens[i]+Sep;
  }
  return _SerialTelegram;
 
}
