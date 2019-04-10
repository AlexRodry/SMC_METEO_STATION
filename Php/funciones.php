<?php
//Devuelve un array multidimensional con el resultado de la consulta
    function getArraySQL($conexion, $sql){
        //generamos la consulta
        if(!$result = mysqli_query($conexion, $sql)) die();

        $rawdata1 = array();
        $rawdata2 = array();
        //guardamos en un array multidimensional todos los datos de la consulta
        $i=0;
		
        while($row = mysqli_fetch_array($result))
        {   
            // guardamos en rawdata todos los vectores/filas que nos devuelve la consulta
            // $rawdata[$i] = $row;
			
			array_push($rawdata1, $rawdata2, $row);
            $i++;
        }
		
        //devolvemos rawdata
        return $rawdata1;
        return $rawdata2;
    }

    function obtener_valores($id_sensor, $conexion){ 

        $arrayDatos = array();
        $sql = "SELECT time, valor FROM data Where idsensor = ". $id_sensor;
		$data = getArraySQL($conexion, $sql); 

	    foreach($data as $row){

            $dAux = array($row['Dia'], $row['Hora'], intval($row['valor']));
            array_push($arrayDatos, $dAux);

        }

        return json_encode($arrayDatos);
        //return $arrayDatos;
       
    }
	?>