##  Обучает нейросеть и выводит относительную ошибку

library('neural')
source('data.r')

for(i in 1:10){
  neurons<- 20;
  data<-rbftrain(x,neurons,y,sigma=NaN,visual=FALSE)

  out <- rbf(x,data$weight,data$dist,data$neurons,data$sigma)
  print(mean(abs(y-out)/y))
}
