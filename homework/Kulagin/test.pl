# for(1..10){
# 	local $_ = 3;
# 	print;
# }

# история ввода
# автодополнение

# tab - доступные команды 
# alias

# хэш
# - кол-во пар-в
# - ф-ю
# eval польз. вводв

# ls -> die

# qx

# Term::Readline

# verbose
# rename

my $a = "AAAAB3NzaC1yc2EAAAADAQABAAABAQDmOZv29Pfrcfe+DAdZW27WpE5vJpfK8AvaG6pWoIrenL3T08yjxU9/eQOevpp4fikQG0JsESYWO1oDM93/UvU6Rw+/tUSw8QpxWqj09Bwx0HnH9zXqoJN5lAIUziF53ZHPtplRbXuHhNYpRuGvZVG7JWM/qg4uQ/WKpfWnB5b2PR6xL02qS5tyU8ENmFW8WLbisi8ILFid2lwpcmTUcRFtv3WVSyeB0iGftXbKv6CRa0/Us4AhgJLGu+bZGSeY9GdvHK64xec+ulrrgfBSAWbuvgWykMYaqKeDNSrYggdxXsdmYhdFj/6/8aAp8JTxGBz171Z2G08clQHk2I8X8Trp";

use DDP;

my @a = split //, $a;

# p @a;

@a = sort @a;

# p @a;
my @c = (4,5,6);

my %b = @c;
# my %b = map { $_, 1} @c;
my %b = %{@c};

p %b;


