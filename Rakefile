require 'rake/loaders/makefile'
require 'pp'

SOURCE_FILES = ['main.cpp']

CXX = "g++"
CXX_FLAGS=['-std=c++11'].join(" ")

file ".depends" => SOURCE_FILES do |t|
  sh "#{CXX} #{CXX_FLAGS} -M -MM -MF - #{t.prerequisites.join(' ')} > #{t.name}"
end

Rake::MakefileLoader.new.load(".depends") if File.file?(".depends")

task :default => ['.depends', :renderschuessel]

task :clean do
  sh "rm renderschuessel *.o .depends || true"
end

rule '.o' => ['.cpp'] do |t|
  sh "#{CXX} #{CXX_FLAGS} #{t.source} -c -o #{t.name}"
end

file 'renderschuessel' => SOURCE_FILES.map{|f| File.basename(f, '.*')+'.o'} do
  sh "#{CXX} #{CXX_FLAGS} -o renderschuessel " + SOURCE_FILES.map{|f| File.basename(f, '.*')+'.o'}.join(" ")
end