set -x
rm source.txt
rm -R ./classes/*
find -name "*.java" > source.txt
javac -d classes @source.txt -classpath ./lib/cloudapi.jar
