require 'digest/md5'

class SourceFile
	@@allLines = Hash.new
	@@allFiles = Hash.new

	def hash(line)
		return Digest::MD5.hexdigest(line)
	end

	def initialize(file)
		if (file.class == String) then
			file = File.open(file)
		end

		num = 0
		@lines = Array.new
		file.each do |line|
			key = hash(line)
			@lines.push(key)
			@@allLines[key] = line
			if block_given? then 
				yield(file.path, num, key, line)
			end
			num += 1
		end
	end
end
