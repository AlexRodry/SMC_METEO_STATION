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
  <div id="chart_div12"></div>
  <div id="chart_div13"></div>
  <div id="chart_div14"></div>
  <div id="chart_div15"></div>
  <div id="chart_div16"></div>
  <div id="chart_div17"></div>
  <div id="filter_div"></div>
  <div id="chart_div18"></div>


<?php
	include ('connectBD.php');
	include ('funciones.php');
    // Conexión con la base de datos
    $conexion = conectarBD();
	
	#JSON con la Fecha - Dato 
    $valor_ane3s = obtener_valores(1, $conexion); //Dato de la media del anemometro cada 3s
	$valor_vel3s = obtener_valores(2, $conexion); //Dato de la media de la veleta cada 3s
	$valor_hum1m = obtener_valores(3, $conexion); //Dato de la humedad cada 1min
	$valor_pre1m = obtener_valores(4, $conexion); //Dato de la presión cada 1min
	$valor_tem1m = obtener_valores(5, $conexion); //Dato de la temperatura cada 1min
	$valor_ane10m = obtener_valores(6, $conexion); //Dato de la media del anemometro cada 10min
	$valor_vel10m = obtener_valores(7, $conexion); //Dato de la media de la veleta cada 10min
	$valor_ane1h = obtener_valores(8, $conexion); //Dato de la media del anemometro cada 1h
	$valor_vel1h = obtener_valores(9, $conexion); //Dato de la media de la veleta cada 1h
	$valor_plu1h = obtener_valores(10, $conexion); //Dato de la media del pluviometro cada 1h
	$valor_plu3h = obtener_valores(11, $conexion); //Dato de la media del pluviometro cada 3h
	$valor_plu1d = obtener_valores(12, $conexion); //Dato de la media del pluviometro cada 1d

	
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
	google.charts.setOnLoadCallback(drawBasic7);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic8);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic9);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic10);
    google.charts.load('current', {packages: ['corechart', 'line']});
	google.charts.setOnLoadCallback(drawBasic11);
    google.charts.load('current', {'packages':['corechart', 'controls']});
	google.charts.setOnLoadCallback(drawBasic12);	

function drawIns1() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Anemometro', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 60, redTo: 90,
          yellowFrom:40, yellowTo: 60,
          minorTicks: 5, max: 90
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div1'));
	
	var valor_anemometro = <?php echo $valor_ane3s;?>;
	var ultimo_anemometro =  valor_anemometro[valor_anemometro.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_anemometro[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns2() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Veleta', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          minorTicks: 5, max: 360
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div2'));

	var valor_veleta = <?php echo $valor_vel3s;?>;
	var ultimo_veleta =  valor_veleta[valor_veleta.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_veleta[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns3() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Humedad', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          minorTicks: 5, max: 100
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div3'));

	var valor_humedad = <?php echo $valor_hum1m;?>;
	var ultimo_humedad  =  valor_humedad [valor_humedad .length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_humedad[1]);
        chart.draw(data, options);
	}, 1000);      
 }	
function drawIns4() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Presión', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          minorTicks: 10000, max: 120000, min: 80000
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div4'));

	var valor_presion = <?php echo $valor_pre1m;?>;
	var ultimo_presion =  valor_presion[valor_presion.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_presion[1]);
        chart.draw(data, options);
	}, 1000);      
 }
function drawIns5() {

      var data = google.visualization.arrayToDataTable([
          ['Label', 'number'],
          ['Temperatura', 0],
        ]);
		 
        var options = {
          width: 600, height: 200,
          redFrom: 40, redTo: 50,
          yellowFrom:35, yellowTo: 40,
          minorTicks: 5, max: 50
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div5'));

	var valor_temperatura = <?php echo $valor_tem1m;?>;
	var ultimo_temperatura =  valor_temperatura[valor_temperatura.length-1];
	
    chart.draw(data, options);
    setInterval(function() {
		data.setValue(0, 1, ultimo_temperatura[1]);
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
          redFrom: 50, redTo: 60,
          yellowFrom:40, yellowTo: 50,
          minorTicks: 5, max: 60
        };
		  
	var chart = new google.visualization.Gauge(document.getElementById('chart_div6'));

	var valor_pluviometro = <?php echo $valor_plu1h;?>;
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
      data.addColumn('number', 'km/h');
	  data.addRows(<?php echo $valor_ane3s;?>);

      var options = {
        title: 'ESTACIÓN METEOROLÓGICA URJC',
         
		hAxis: {
          title: 'Tiempo',
        },
        
        vAxis: {
          title: 'Velocidad del viento cada 3s',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div7'));
      chart.draw(data, options);
	  
    }
function drawBasic2() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'grados');
	  data.addRows(<?php echo $valor_vel3s;?>);

      var options = {
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Dirección del viento cada 3s',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div8'));
      chart.draw(data, options);
    }
	
	function drawBasic3() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', '%');
	  data.addRows(<?php echo $valor_hum1m;?>);

      var options = {  
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Humedad cada 1 min',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div9'));
      chart.draw(data, options);
    }
	
	function drawBasic4() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'Pa');
	  data.addRows(<?php echo $valor_pre1m;?>);

      var options = {
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Presión cada 1 min',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div10'));
      chart.draw(data, options);
    }
	
	function drawBasic5() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'ºC');
	  data.addRows(<?php echo $valor_tem1m;?>);

      var options = {
    
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Temperatura cada 1 min',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div11'));
      chart.draw(data, options);
    }
	function drawBasic6() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'km/h');
	  data.addRows(<?php echo $valor_ane10m;?>);

      var options = {

		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Velocidad del viento cada 10 min',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div12'));
      chart.draw(data, options);
    }
	function drawBasic7() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'grados');
	  data.addRows(<?php echo $valor_vel10m;?>);

      var options = {
   
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Dirección del viento cada 10 min',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div13'));
      chart.draw(data, options);
    }
	function drawBasic8() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'km/h');
	  data.addRows(<?php echo $valor_ane1h;?>);

      var options = {
   
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Velocidad del viento cada 1 hora',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div14'));
      chart.draw(data, options);
    }
	function drawBasic9() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'grados');
	  data.addRows(<?php echo $valor_vel1h;?>);

      var options = {
    
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Dirección del viento cada 1 hora',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div15'));
      chart.draw(data, options);
    }
	function drawBasic10() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'mm');
	  data.addRows(<?php echo $valor_plu1h;?>);

      var options = {

		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Pluviómetro cada 1 hora',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div16'));
      chart.draw(data, options);
    }
	function drawBasic11() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'mm');
	  data.addRows(<?php echo $valor_plu3h;?>);

      var options = {
    
		hAxis: {
          title: 'Tiempo',
		  
        },
        
        vAxis: {
          title: 'Pluviómetro cada 3 horas',
        }
      };

      var chart = new google.visualization.LineChart(document.getElementById('chart_div17'));
      chart.draw(data, options);
    }
	function drawBasic12() {
	
      var data = new google.visualization.DataTable();
      data.addColumn('string', 'Fecha');
      data.addColumn('number', 'mm');
	  data.addRows(<?php echo $valor_plu1d;?>);
	  
	  // Create a dashboard.
      var dashboard = new google.visualization.Dashboard(document.getElementById('dashboard_div'));

      // Creamos el control
      var RangeSlider = new google.visualization.ControlWrapper({
        'controlType': 'CategoryFilter',
        'containerId': 'filter_div',
        'options': {
          'filterColumnLabel': 'Fecha'
        }
      });

      // Create a pie chart, passing some options
      var LineChart = new google.visualization.ChartWrapper({
        'chartType': 'LineChart',
        'containerId': 'chart_div18',
        'options': {
		 'hAxis':{
		'title':'Tiempo',
		 },
		 'vAxis':{
		'title':'Pluviómetro cada 1 dia',
		 },			  
          'pieSliceText': 'value',
          'legend': 'right'
        }
        });

       dashboard.bind(RangeSlider, LineChart);
	   dashboard.draw(data);
    }
</script>