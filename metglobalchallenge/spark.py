from __future__ import print_function

from pyspark.conf import SparkConf

from pyspark.sql import SparkSession, Row
from pyspark.sql import functions as func

from pyspark.sql.types import *

# Solution to the 1st part of the challenge
# takes spark session instance as an input argument
def part1(spark):

	# read/write file pathes
	read_file = "/home/iorkhan/Dropbox/metglobal/datasets/hotels_search.log"
	# part1.csv is treated as a directory which is OK. The single output file will be inside it.
	write_file = "/home/iorkhan/Dropbox/metglobal/datasets/part1.csv"

	# reads json file and creates temporary view for further quering 
	df = spark.read.json( read_file )
	df.createOrReplaceTempView("table")
	# uses lateral view explode function to flatten the nested arrays
	tabulo = spark.sql("SELECT \
									product.providers[0] AS Provider, \
									product.hotel_code AS HotelCode, \
									room.room_category AS RoomCategory, \
									room.room_type AS RoomType, \
									product.meal_type AS MealType, \
									product.cost AS Cost\
									FROM table \
										lateral view explode(products) exploded_products as product \
										lateral view explode(product.rooms) exploded_rooms as room")
	
	tabulo.show()
	# writes the results into a single CSV file while retaining the headers information
	tabulo.repartition(1).write.csv(path=write_file, mode="overwrite", header=True)


# Solution to the 2nd part of the challenge
# takes spark session instance as an input argument
def part2(spark):

	#read/write file path
	read_file = "/home/iorkhan/Dropbox/metglobal/datasets/part1.csv"
	# part2.csv is treated as a directory which is OK. The single output file will be inside it.
	write_file = "/home/iorkhan/Dropbox/metglobal/datasets/part2.csv"
	
	# inferSchema is set to be True in order to infer the data types correctly e.g. cost -> double
	df = spark.read.csv(path=read_file, sep=',', header=True, inferSchema=True)
	# calculates average cost per hotel under the column name "AverageCost"
	ave_result = df.groupBy("HotelCode").agg(func.mean("Cost").alias("AverageCost"))
	# rounds the "AverageCost" column to 2 decimal places and saves under the column name "RoundedAverageCost"
	round_result = ave_result.withColumn( "RoundedAverageCost", func.round( ave_result["AverageCost"], scale=2 ) )
	round_result.show()
	# writes the results into a single CSV file while retaining the headers information
	round_result.repartition(1).write.csv(path=write_file, mode="overwrite", header=True)



if __name__ == "__main__":
	# creates the session instance 
	spark = SparkSession.builder \
		.master("local[4]") \
		.appName("MetGlobalChallenge") \
		.config(conf=SparkConf()) \
		.getOrCreate()

	# calls the user defined functions
	part1(spark)
	part2(spark)

	# stops the operations 
	spark.stop()