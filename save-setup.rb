$name = ARGV.join('_')
$dir = "experiments/#{$name}"
`mkdir -p #{$dir}`
`./build-release`
`cp run config/sim_config.hpp kcache/kcache_config.hpp models/client_model.cpp #{$dir}`

