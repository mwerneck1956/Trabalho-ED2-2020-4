echo "Digite o caminho do arquivo csv"
read txt_path

g++ -o main *.cpp
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
   ./main $txt_path
else
   echo "nao compilado"
fi
