require "src/all"

class SourceFile
	include StrS

	attr_reader :filename

	def initialize(file)
		if (file.class == String) then
			@filename = file
			file = File.open(file)
		else
			@filename = file.path
		end

		num = 0
		@lines = Array.new
		file.each do |content|
			num += 1
			line = Line.new(self, num, content)
			@lines.push(line)

			if block_given? then 
				yield(line)
			end
		end
	end

	def SourceFile.getLine(key)
		return @@allLines[key]
	end

	def each
		@lines.each { |l| yield(l) }
	end

	def [](num)
		return @lines[num - 1]
	end

	def ==(file)
		return false unless file.respond_to?(:filename)
		return @filename == file.filename
	end

	def to_s
		return @filename
	end

	def size
		return @lines.size
	end
end

