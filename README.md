# create
Handy tool for creating various default files

## Compile with

```
gcc create.c -o create
```

(I was lazy so the output file name is important. If you want the output file to have a different name change the NAME value on [create.c](https://github.com/SirMorland/create/blob/master/create.c).)

Output file must be in the same folder as `defaults` folder.

## Usage

### Create alias for ease of use

Create alias for compiled `create` file. Add

```
alias create='/absolute/path/create/create'
```

to `~/.bash_aliases` and restart terminal or

```
source ~/.bash_aliases
```

### Basic usage

```
create filetype -o filename
```

Use

```
create -h
```

to get help.

## Currently supported file types:

| Language | File type |
|---|---|
| C | c |
| C++ | cpp |
| C# | cs |
| Java | java |
| HTML | html |
| CSS | css |
| JavaScript| js |
| PHP | php |

You can add your own file types anytime by just creating a `my-file-type.my-file-type` file to `defaults` folder.
