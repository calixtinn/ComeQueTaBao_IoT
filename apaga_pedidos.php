<?php 
		
	$link = mysqli_connect('localhost', 'root', 'root', 'ComeQueTaBao');
	$sql = "TRUNCATE ComeQueTaBao.Pedido;"
	if ($link->query($sql) === TRUE) {
		echo "Pedidos Deletados!"
	}
	else {
		echo "Error: " . $sql . "<br>" . $link->error;
		}							
	}
	$link->close();
 ?>

