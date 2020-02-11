/*.......................................................................*/
/*.......................Función de codificación.........................*/
/*.......................................................................*/
String _SerialTelegram;   // String temporal

String encodeTelegram(){
  /* Cabecera del telegrama */
  _SerialTelegram = "nombre"+Sep+St+Sep+ "Fecha"+Sep+fecha+Sep; 
  /* Cadena identificador + valor del sensor */
  for (int i=0; i<=nids-1; i++){
    _SerialTelegram += ids[i]+Sep+sens[i]+Sep;
  }
  /* Telegrama codificado */
  return _SerialTelegram;
}

/* Resultado de un telegrama ya codificado ejemplo :
   nombre|ST01|Fecha|20200209014919|1|55|2|95033|3|23.72|4|90|5|16.80|6|1.96|10|rssi|
 */
