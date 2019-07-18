$root = "#{`pwd`.strip}/experiments"

Dir.foreach($root) do |item|
  next if item == '.' || item == '..'
  Dir.chdir "#{$root}/#{item}"
  puts "running #{item}"
  `./run`
end
