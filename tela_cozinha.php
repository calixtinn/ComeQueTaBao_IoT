<html>
<head>
<meta http-equiv="refresh" content="5">
</head>
<body>

<h1>Lista de Pedidos</h1>
<table border="1">
<tr>
   <td width="50px"><b>ID Pedido</b></td>
   <td width="50px"><b>Mesa</b></td>
   <td width="200px"><b>Prato</b></td>
   <td width="100px"><b>Quantidade</b></td>
   <td width="100px"><b>Hora do Pedido</b></td>

</tr>
<?php
$link = mysqli_connect('localhost', 'root', 'root', 'ComeQueTaBao');
if (mysqli_connect_errno()){
echo "Falha ao conectar";
}
mysqli_select_db($link,"ComeQueTaBao");
$sql = "SELECT Pedido.pe_id, Mesa.me_num, Item.it_name, Pedido.pe_qtde, Pedido.pe_hora FROM Pedido INNER JOIN Mesa on Mesa.me_id=Pedido.me_id INNER JOIN Item on Item.it_id=Pedido.it_id";
$result = $link->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
?>
   <tr>
      <td><?php echo $row['pe_id']; ?></td>
      <td><?php echo $row['me_num']; ?></td>
      <td><?php echo $row['it_name']; ?></td>
	  <td><?php echo $row['pe_qtde']; ?></td>
	  <td><?php echo $row['pe_hora']; ?></td>
   </tr>
<?php
    }
} else {
    echo "0 results";
}
$link->close();
?>
   
</table>
</body>
</html>
