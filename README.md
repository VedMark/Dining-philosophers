# Dining-philosophers

Dining philosophers problem solution for process synchronization.

## Task

Five philosophers, Kant, Spinoza, Nietzsche, Schopenhauer and Sartre spend their time thinking and eating spaghetti. They eat at a round table with five individual seats. For eating each philosopher needs two forks (the resources). There are five forks on the table, one left and one right of each seat. When a philosopher cannot grab both forks it sits and waits. Eating takes random time, then the philosopher puts the forks down and leaves the dining room. After spending some random time thinking about the nature of the universe, he again becomes hungry, and the circle repeats itself.

## Getting Started

### Requirements
  - Unix
  - Bash
  - C++ compiler supporting the C++11 standard
  
### Installing

1. Clone project.
2. Run make.

```
git clone https://github.com/VedMark/Dining-philosophers.git
cmake CMakeLists.txt
make
```

### Running

```
./run.sh
```
