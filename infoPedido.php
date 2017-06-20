<html>
<head>

	<meta charset='utf-8'>
    <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>
    <meta http-equiv='x-ua-compatible' content='ie=edge'>

    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.4/css/bootstrap.min.css' integrity='2hfp1SzUoho7/TsGGGDaFdsuuDL0LX2hnUp6VkX3CUQ2K4K+xjboZdsXyp4oUHZj' crossorigin='anonymous'>
      
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  	
    <script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.2.0/js/tether.min.js' integrity='sha384-Plbmg8JY28KFelvJVai01l8WyZzrYWG825m+cZ0eDDS1f7d/js6ikvy1+X+guPIB' crossorigin='anonymous'></script>
    
    <script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.4/js/bootstrap.min.js' integrity='VjEeINv9OSwtWFLAtmc4JCtEJXXBub00gtSnszmspDLCtC0I4z4nqz7rEFbIZLLU' crossorigin='anonymous'></script>
    
    <title>ComeQueTaBao</title>
    
 </head> 
  
 <body> 
  
    <nav class='navbar navbar-fixed-top navbar-dark bg-inverse bg-faded'>
        <font class='lead'>Auto Atendimento</font>
    </nav>
  
    <div class='container-fluid'>
        
        <div class='row'>
  
            <div class='col-lg-2 col-md-2 col-sm-12'></div>
  
            <div class='col-lg-8 col-md-8 col-sm-12'> 

            	<br><br><br>

            	Pedido:
                <?php
                    echo $_GET['mesa'];
                    
                ?>  

            	<br><br>
                                
                <?php
					
					echo $_GET['pedidoFinal']."<br><br>";
					//echo "Valor do pedido final: ";
					//echo "R$".$_GET['valorFinal'];
				?>

				<?php	
						$link = mysqli_connect('localhost', 'root', 'root', 'ComeQueTaBao');
						$mesa = substr($_GET['mesa'], 4);
						$ped_final = $_GET['pedidoFinal'];
						$itens = explode(" <br>", $ped_final);
						// Para cada item 					
			
						for ($i = 0; $i < count($itens)-1; $i++){
    
    						$qtde = substr($itens[$i],0,1);
							$prato = substr($itens[$i],4);
							
							if ($prato == "Macarrão na chapa"){
								$id_food = 1;
								$valor_food = 7;
							}
							
							elseif ($prato == "Espetinho") {
								$id_food = 4;
								$valor_food = 7;
							}
							
							elseif ($prato == "Panqueca") {
								$id_food = 2;
								$valor_food = 15;
							}
						
							elseif ($prato == "Fritas") {
								$id_food = 3;
								$valor_food = 10;
							}
							
							$sql = "INSERT INTO Pedido (pe_valor, pe_qtde, pe_hora, me_id, it_id) 
									VALUES ('$valor_food', '$qtde', CURRENT_TIME(), '$mesa', '$id_food')";
							if ($link->query($sql) === TRUE) {
									//echo "Pedido adicionado ao banco ";
							}
							else {
									echo "Error: " . $sql . "<br>" . $link->error;
							}							
						}
						$link->close();

						if (mysqli_connect_errno()){
							echo "Falha ao conectar";
						}
				?>

              O seu pedido foi enviado à cozinha e logo estará pronto!

			</div>
				                    
            
            <div class='col-lg-2 col-md-2 col-sm-12'></div>
         

    	</div>  
    
    </div> 

    <nav class='navbar navbar-fixed-bottom bg-faded'>
        <p class='lead' align='center'>ComeQueTaBao</p>
    </nav>

</body>
  
</html>
