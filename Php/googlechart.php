  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <div id="chart_div"></div>


<?php
	include ('connectBD.php');
	include ('funciones.php');
    // Conexión con la base de datos
    $conexion = conectarBD();

	#JSON con el dia - Hora - Dato 
    $valor_ane3s = obtener_valores(1, $conexion); //Dato de la media del anemometro cada 3s

	desconectarBD($conexion);
  ?>


<script>
/*     google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic1);
	
function drawBasic1() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Dia');
      data.addColumn('string', 'Hora');
      data.addColumn('number', 'km/h');
	  data.addRows(<?php echo $valor_ane3s;?>);

      var options = {
        title: 'URJC',
        curveType: 'function',
        
        
        vAxis: {
          title: 'Temperatura',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div2'));
      chart.draw(data, options);   
    }*/

</script>