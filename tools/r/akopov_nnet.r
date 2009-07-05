library(neural)
library(nnet)
source('data.r')

################# тест на многослойном персептроне #################

## вспомогательная функция взвешенной суммы
center.of.gravity <- function(alphas, ys) {
  crossprod(alphas, ys) / sum(alphas)
}
## количество скрытых нейронов
hidden.neurons <- 20

## обучение сети
x.count <- sample(nrow(x),round(nrow(x)/2))
ann <- nnet(x[x.count,], class.ind(y), size=hidden.neurons,rang = 0.1, decay = 5e-4, maxit = 500 )

## проверка способности сети к распознаванию
test <- function(ann,y,xtest) {
  apply(xtest, 1, function(x) {
    center.of.gravity(as.vector(predict(ann,x)),as.numeric(levels(factor(y))))
  })
}

## вывод на экран предсказанного значения выхода на тестовых тестовых испытаниях
test_data <- 1:nrow(x) #sample(nrow(x),nrow(x))
result <- test(ann,y,x[test_data,])
print(
      result
      )


evl <- function(a,b) {
  re <- 100* abs(a-b) / a
  data.frame(data=re,mean=mean(re), max=max(re))
}

t <- function() {
  evl(y[test_data],result)
}
