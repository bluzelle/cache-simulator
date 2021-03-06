$runs = ARGV.shift
$work = []
$wake_interval = 300
$max_concurrent = 10;

$runs.to_i.times do 
  ARGV.each{|spec| $work.push spec}
end

$running_jobs = 0
$running_jobs_mutex = Mutex.new

`./build-release`

until $work.empty?
  memdata = `free`.split
  total = memdata[7].to_i
  avail = memdata[12].to_i
  perc = (100.0*avail)/total

  puts "#{avail}/#{total} bytes free (#{perc.to_i}%)"
  puts "#{$running_jobs} jobs currently running"

  if perc < 50
    puts "waiting for more memory"
    sleep($wake_interval)
  end

  if $running_jobs >= $max_concurrent
    puts "waiting for jobs to finish"
    sleep($wake_interval)
  end

  task = $work.shift

  Thread.new do 
    $running_jobs_mutex.synchronize{ $running_jobs += 1 }
    puts "starting a run of #{task}"
    `./run #{task} > /dev/null`
    $running_jobs_mutex.synchronize{ $running_jobs -= 1 }
    puts "finished a run of #{task}"
  end

  sleep($wake_interval)
end

