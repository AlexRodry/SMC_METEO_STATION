  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
  <div id="chart_div1"></div>
  <div id="chart_div2"></div>
  <div id="chart_div3"></div>
  <div id="chart_div4"></div>
  <div id="chart_div5"></div>
  <div id="chart_div6"></div>
  <div id="chart_div7"></div>
  <div id="chart_div8"></div>
  <div id="chart_div9"></div>
  <div id="chart_div10"></div>
  <div id="chart_div11"></div>

<?php
	include ('connectBD.php');
	include ('funciones.php');
    // Conexión con la base de datos
    $conexion = conectarBD();
	
	#JSON con la Fecha - Dato 
  $valor_hum = obtener_valores(1, $conexion);   //Dato de la humedad
	$valor_pres = obtener_valores(2, $conexion);  //Dato de la presión
	$valor_temp = obtener_valores(3, $conexion);  //Dato de la temperatura
	$valor_dir = obtener_valores(4, $conexion);   //Dato de la dirección del viento
	$valor_anem = obtener_valores(5, $conexion);  //Dato de la velocidad del viento
	$valor_pluv = obtener_valores(6, $conexion);  //Dato de la lluvia	
	desconectarBD($conexion);
  ?>


<script>

//Gráficos instantáneos
 	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns1); 
	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns2); 
 	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns3); 
 	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns4); 
 	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns5); 
 	google.charts.load('current', {packages: ['gauge']});
	google.charts.setOnLoadCallback(drawIns6);
//Gráficos lineales	
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic1);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic2);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic3);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic4);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic5);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic6);
    google.charts.load('current', {packages: ['corechart', 'line']});
function drawIns1() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Humedad', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 0, redTo: 40,
          yellowFrom:40, yellowTo: 50,
          greenFrom:50, greenTo: 60,
          minorTicks: 5, max: 100
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div1'));
	
	var valor_humedad = <?php echo $valor_hum;?>;
	var ultimo_humedad =  valor_humedad[valor_humedad.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_humedad[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns2() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Presión', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          minorTicks: 10000, max: 120000, min: 80000
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div2'));

	var valor_presion = <?php echo $valor_pres;?>;
	var ultimo_presion =  valor_presion[valor_presion.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_presion[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns3() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Temperatura', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 25, redTo: 35,
          yellowFrom:23, yellowTo: 25,
          greenFrom:19, greenTo: 23,
          minorTicks: 1, max: 35
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div3'));

	var valor_temperatura = <?php echo $valor_temp;?>;
	var ultimo_temperatura =  valor_temperatura[valor_temperatura.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_temperatura[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns4() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Dirección', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          minorTicks: 0, max: 360, min: 0
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div4'));

	var valor_direccion = <?php echo $valor_dir;?>;
	var ultimo_direccion =  valor_direccion[valor_direccion.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_direccion[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns5() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Anemometro', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 10, redTo: 15,
          yellowFrom:5, yellowTo: 10,
          minorTicks: 5, max: 15
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div5'));

	var valor_anemometro = <?php echo $valor_anem;?>;
	var ultimo_anemometro =  valor_anemometro[valor_anemometro.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_anemometro[1]);
        chart.draw(data, options);
	}, 1000);      
 }	
function drawIns6() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Lluvia', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 15, redTo: 20,
          yellowFrom:10, yellowTo: 15,
          minorTicks: 5, max: 20
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div6'));

	var valor_pluviometro = <?php echo $valor_pluv;?>;
	var ultimo_pluviometro =  valor_pluviometro[valor_pluviometro.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_pluviometro[1]);
        chart.draw(data, options);
	}, 1000);      
 }	 
function drawBasic1() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', '%HR');
	  data.addRows(<?php echo $valor_hum;?>);

      var options = {
        title: 'ESTACIÓN METEOROLÓGICA URJC',
         
		hAxis: {
          title: 'Tiempo',
        },
        
        vAxis: {
          title: 'Humedad relativa',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div7'));
      chart.draw(data, options);
	  
    }
function drawBasic2() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'Pa');
	  data.addRows(<?php echo $valor_pres;?>);

      var options = {
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Presión',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div8'));
      chart.draw(data, options);
    }
	
	function drawBasic3() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'ºC');
	  data.addRows(<?php echo $valor_temp;?>);

      var options = {  
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Temperatura',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div9'));
      chart.draw(data, options);
    }
	
	function drawBasic4() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'Grados');
	  data.addRows(<?php echo $valor_dir;?>);

      var options = {
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Dirección del viento',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div10'));
      chart.draw(data, options);
    }
	
	function drawBasic5() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'km/h');
	  data.addRows(<?php echo $valor_anem;?>);

      var options = {
    
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Velocidad viento',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div11'));
      chart.draw(data, options);
    }
	function drawBasic6() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'mm');
	  data.addRows(<?php echo $valor_pluv;?>);

      var options = {

		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Precipitaciones',
        }
      };
    }
</script>