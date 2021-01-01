g++ -o main *.cpp
if [ $? -eq 0 ];then 
   echo "compilado com sucesso!"
   ./main
else
   echo "nao compilado"
fi