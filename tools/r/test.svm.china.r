library('e1071')

data=read.table("china.data",sep=";")
y=data[,9]
x=data[c(1:8)]
#svm.model <- svm(y)
#svm.pred <- predict(svm.model,x)


mixture.svm.test <- function(xs.train, ys.train, xs.test=xs.train, ys.test=ys.train, cost=1000, gamma=1E-4) {
  trainset <- as.data.frame(xs.train)
  trainset$Y <-  ys.train
  svm.model <- svm(Y ~ ., data = trainset, cost = cost, gamma = gamma);
  testset <- as.data.frame(xs.test)
  svm.pred <- predict(svm.model, testset)
} ## assert(0.15 > mixture.svm.test(matrix(1:6,nrow=2), 1:2))    

## 100*mean(apply(as.matrix(rep(0.5,30)), 1, t))
run <- function(f) {
  i <- sample(nrow(x),round(f*nrow(x))); 
  nx=x[i,]
  ny=y[i]
  ##
  ap.y=mixture.svm.test(nx,ny,x,y,gamma=1e-1)
  # data.frame(delta=abs(y-ap.y),mean=mean(abs(y-ap.y)/y))
  abs(y-ap.y)
}

delta <- run(0.5) # 0.5 - размер обучающей выборки


mixture.lm.test <- function(xs.train, ys.train, xs.test=xs.train, ys.test=ys.train, cost=1000, gamma=1E-4) {
  trainset <- as.data.frame(xs.train)
  trainset$Y <-  ys.train
  svm.model <- lm(Y ~ ., data = trainset, cost = cost, gamma = gamma);
  testset <- as.data.frame(xs.test)
  pred <- predict(svm.model, testset)
} ## assert(0.15 > mixture.svm.test(matrix(1:6,nrow=2), 1:2))    

lm.run <- function(f) {
  i <- sample(nrow(x),round(f*nrow(x))); 
  nx=x[i,]
  ny=y[i]
  ##
  ap.y=mixture.lm.test(nx,ny,x,y,gamma=1e-1)
  # data.frame(delta=abs(y-ap.y),mean=mean(abs(y-ap.y)/y))
  abs(y-ap.y)
}

delta.lm <- lm.run(0.5) # 0.5 - размер обучающей выборки
