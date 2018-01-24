# UoYWeek
UoYWeek gives the current date string formatted as used by the [University of York](https://www.york.ac.uk/). For example, `spr/3/wed` would refer to Wednesday on the 3rd week of Spring term.

## Installing
### Linux/Mac
```bash
# Clone the repository
git clone https://github.com/LukeMoll/uoyweek.git
cd uoyweek
# Compile
make uoyweek
chmod +x uoyweek
```
You now have an executable file, `uoyweek`. To run it while you're in `uoyweek/`, just type `./uoyweek`. You'll probably want it in a more useful place though.
```bash
sudo mv uoyweek /usr/bin
```
You should now be able to run `uoyweek` from any directory.

<!-- TODO Windows instructions -->
