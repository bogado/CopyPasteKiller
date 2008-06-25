require "digest/md5"
require "src/all"

class Line
	include StrS
	@@allLines = Hash.new
	@@hasher = Hasher.new

	attr_accessor :file
	attr_accessor :num
	attr_accessor :key

	def initialize(file, num, content)
		@file = file
		@num = num
		@key = @@hasher.hash(content)
		@@allLines[@key] = content
	end

	def Line.hasher=(hasher)
		@@hasher = hasher
	end

	def Line.hasher
		return @@hasher
	end

	def to_s
		return "#{file}:#{num}"
	end

	def ==(line)
		return false unless line.respond_to?(:key)
		return line.key == @key
	end

	def ===(line)
		return line.num == @num && line.file == @file
	end

	def next
		return @file[@num + 1]
	end

	def +(num)
		return @file[@num + num]
	end

	def -(num)
		return @file[@num - num]
	end

	def Line.[](key)
		if key.class == Line
			key = key.key
		end

		return @@allLines[key]
	end
end

