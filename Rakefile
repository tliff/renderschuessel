require 'rake/loaders/makefile'
require 'pp'

SOURCE_FILES = Dir['src/*.cpp']
TEST_FILES = Dir['test/*.cpp']

CXX = "g++"
LD_FLAGS = []
LD_TEST_FLAGS=LD_FLAGS + ['-pthread']
CXX_FLAGS=['-g -std=c++11']
CXX_TEST_FLAGS=CXX_FLAGS+['-isystem/opt/local/gtest/include', '-I/opt/local/gtest','-Isrc']


file ".build/src/.depends" => Dir['src/**/*.cpp'] do |t|
  sh "rm -f .build/src/.depends"
  t.prerequisites.each do |name|
    sh "#{CXX} #{CXX_FLAGS.join(' ')}  -M -MM -MT #{'.build/' if name=~/\.cpp$/}#{name.sub('.cpp','.o')} #{name} >> #{t.name}"
  end
  Rake::MakefileLoader.new.load(".build/src/.depends")
end
Rake::MakefileLoader.new.load(".build/src/.depends") if File.exists?(".build/src/.depends")

file ".build/test/.depends" => Dir['src/**/*.cpp'] + Dir['test/**/*.cpp']  do |t|
  sh "rm -f .build/test/.depends"
  t.prerequisites.each do |name|
    sh "#{CXX} #{CXX_TEST_FLAGS.join(' ')}  -M -MM -MT #{'.build/' if name=~/\.cpp$/}#{name.sub('.cpp','.o')} #{name} >> #{t.name}"
  end
  Rake::MakefileLoader.new.load(".build/test/.depends")
end



task :default => ['.build/src/.depends', 'bin/renderschuessel']

task :runtest => [:test] do
  sh './bin/renderschuessel_test'
end

task :test => ['.build/test/.depends', "bin/renderschuessel_test"]

task :clean do
  sh "rm -f renderschuessel_test bin/renderschuessel .build/test/* .build/src/* .build/src/.depends .build/test/.depends"
end

rule('.o' => [proc {|t| t.sub('.build/','').gsub(/\.o$/,'.cpp')}]) do |t|
  flags = t.source =~ /test\// ? CXX_TEST_FLAGS : CXX_FLAGS 
  sh "#{CXX} #{flags.join(' ')} #{t.source} -c -o #{t.name.gsub(/\.cpp$/,'.o')}"
end

file 'bin/renderschuessel' => SOURCE_FILES.map{|f| '.build/src/'+File.basename(f, '.*')+'.o'} do |t|
  sh "#{CXX} #{CXX_FLAGS.join(' ')} -o bin/renderschuessel " +  SOURCE_FILES.map{|f| " .build/src/" +File.basename(f, '.*')+'.o'}.join(" ") + ' ' + LD_FLAGS.join(' ')
end

file 'bin/renderschuessel_test' => TEST_FILES.map{|f| '.build/test/'+File.basename(f, '.*')+'.o'} do |t|
  sh "#{CXX} #{CXX_TEST_FLAGS.join(' ')} -o bin/renderschuessel_test " + TEST_FILES.map{|f| " .build/test/"+File.basename(f, '.*')+'.o'} .join(" ") + ' ' + LD_TEST_FLAGS.join(' ') + ' test/libgtest.a'
end

