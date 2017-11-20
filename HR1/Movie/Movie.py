import urllib2
import pprint
import json
import sys


class Parser(object):
	def __init__(self, substr):
		self.base = "https://jsonmock.hackerrank.com/api/movies/search/?"
		self.lock = 0
		self.page = 0
		self.per_page = 0
		self.total = 0
		self.total_pages = 0
		self.search_query = self.compile_query( self.base, substr, self.page )
		self.response = self.parse()

	def compile_query(self, base, substr, page):
		if self.lock ==0:
			return base+"Title={0}".format( substr )
		else:
			return base+"Title={0}&page={1}".format( substr, page )

	def parse(self):
		response = json.loads( urllib2.urlopen(self.search_query).read() )
		if response["total"] > 0:
			if self.lock == 0:
				self.lock = self.lock + 1
				self.total = response["total"]
				self.total_pages = response["total_pages"]
			self.page = response["page"]
			self.per_page = response["per_page"]
		return response




if __name__=="__main__":
	
	substr = "spider"

	if substr == "":
		sys.exit("Missing movie name")

	with open("output.txt", "w") as file:
		titles = []
		parser = Parser(substr)
		
		if parser.total_pages > 0:
			for page in range( 1, parser.total_pages+1 ):
				parser.search_query = parser.compile_query( parser.base, substr, page )
				parser.response = parser.parse()
				for movie in parser.response["data"]:
					titles.append(movie["Title"])

		if (len(titles)>0):
			titles.sort()

		for title in titles:
			print title
			file.write(title+ "\n")



