task default: "euler"

source_files = FileList[ "*.c" ]
object_files = source_files.ext(".o")
cflags = "-g -O2 -Wall --std=gnu99"

multitask "euler" => object_files do
  sh "gcc #{cflags} #{object_files} -o euler -lm -lgmp"
end

rule ".o" => [".c", "euler.h"] do |t|
  sh "gcc #{cflags} -c -o #{t.name} #{t.source}"
end

task :clean do
  sh "rm -f #{object_files} euler"
end
