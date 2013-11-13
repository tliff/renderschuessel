require 'rake/loaders/makefile'
require 'pp'

SOURCE_FILES = ['src/main.cpp']
TEST_FILES = Dir['test/*.cpp']

CXX = "g++"
LD_FLAGS = []
LD_TEST_FLAGS=LD_FLAGS + ['-pthread']
CXX_FLAGS=['-std=c++11']
CXX_TEST_FLAGS=CXX_FLAGS+['-isystem/opt/local/gtest/include', '-I/opt/local/gtest','-Isrc']



file ".depends" => SOURCE_FILES do |t|
  sh "#{CXX} #{CXX_FLAGS.join(' ')} -M -MM -MF - #{t.prerequisites.join(' ')} > #{t.name}"
end

file "test/.depends" => TEST_FILES do |t|
  sh "#{CXX} #{CXX_TEST_FLAGS.join(' ')}  -M -MM -MF - #{t.prerequisites.join(' ')} > #{t.name}"
end


Rake::MakefileLoader.new.load(".depends") if File.file?(".depends")

task :default => ['.depends', 'bin/renderschuessel']

task :runtest => [:test] do
  sh './bin/renderschuessel_test'
end

task :test => ['test/.depends', "bin/renderschuessel_test"]

task :clean do
  sh "rm -f renderschuessel_test bin/renderschuessel .build/test/* .build/src/* .depends test/.depends"
end

rule('.o' => [proc {|t| t.sub('.build/','').gsub(/\.o$/,'.cpp')}]) do |t|
  flags = t.source =~ /test\// ? CXX_TEST_FLAGS : CXX_FLAGS 
  sh "#{CXX} #{flags.join(' ')} #{t.source} -c -o #{t.name.gsub(/\.cpp$/,'.o')}"
end


file 'bin/renderschuessel' => SOURCE_FILES.map{|f| '.build/src/'+File.basename(f, '.*')+'.o'} do |t|
  sh "#{CXX} #{CXX_FLAGS.join(' ')} -o bin/renderschuessel " +  SOURCE_FILES.map{|f| " .build/src/" +File.basename(f, '.*')+'.o'}.join(" ") + ' ' + LD_FLAGS.join(' ')
end

file 'bin/renderschuessel_test' => TEST_FILES.map{|f| '.build/test/'+File.basename(f, '.*')+'.o'} do
  sh "#{CXX} #{CXX_TEST_FLAGS.join(' ')} -o bin/renderschuessel_test " + TEST_FILES.map{|f| " .build/test/"+File.basename(f, '.*')+'.o'} .join(" ") + ' ' + LD_TEST_FLAGS.join(' ') + ' test/libgtest.a'
end

