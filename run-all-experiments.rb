$root = "#{`pwd`.strip}/experiments"

Dir.foreach($root) do |item|
  next if item == '.' || item == '..'
  Dir.chdir "#{$root}/#{item}"
  puts "running #{item}"
  if File.exist?('done')
    puts "already done; skipping..."
    next
  end
  `./run`
  `touch done`
end
