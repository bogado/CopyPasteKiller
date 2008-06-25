require "src/all"

class LineCache 
	def initialize
		@lines = {}
	end

	def has?(thing)
		case thing
		when Array
			hasLines?(thing)
		when Line
			hasLine?(thing)
		else
			raise
		end
	end

	def hasLines?(lines)
		lines.each { |l| return true if hasLine?(l) }
		return false
	end

	def hasLine?(line)
		return @lines[line.to_s] == 1
	end

	def add(thing)
		case thing 
		when Chunk 
			addChunk(thing)
		when Line
			addLine(thing)
		else 
			raise 
		end
	end

	def addChunk(chunk)
		chunk.size.times do |n| 
			addLine(chunk.line + n)
		end
	end

	def addLine(line)
		@lines[line.to_s] = 1
	end
end

class LineIndexer
	def initialize
		@lines = {}
		@alllines = []
		@files = {}
	end

	def add(filename)
		@files[filename] = 
			SourceFile.new(filename) do |line|

			key = line.key

			if (@lines[key] == nil) then 
				@lines[key] = [] 
			end

			@alllines.push(line)
			@lines[key].push(line)
		end
	end

	def check(min = 2)
		result = []

		cache = LineCache.new

		n = 0
		@alllines.each do |l|
			lines = @lines[l.key]

			yield(n, @alllines.size, l) if block_given?
			n += 1;

			next if lines.size == 1

			next if cache.has?(l)

			matches = lines.map { |line| Chunk.new(line, 1) }

			mychunk = Chunk.new(l, 1)
			while matches.size > 1
				mychunk = mychunk.grow

				newmatches = matches.map do |chunk|
					newchunk = chunk.grow
					if newchunk == mychunk
						newchunk
					else
						nil
					end
				end

				newmatches.compact!

				if (newmatches.size < 2)
					matches.each { |c| cache.add(c) }
					result.push(matches) unless matches[0].size < min
				end

				matches = newmatches
			end
		end

		return result
	end
end

