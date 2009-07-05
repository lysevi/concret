
draw.field<- function(src){
  ftns=read.table(src,sep=";");
  plot(ftns[,1],type="l");
}

ps.field <- function(src,dst){
  postscript(file=dst);
  draw.field(src);
  dev.off();
}
