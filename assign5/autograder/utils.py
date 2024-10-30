AUTOGRADER_PACKAGES = ["colorama==0.4.6"]

def check_virtualenv():
    import sys
    import os
    import subprocess

    if not hasattr(sys, "real_prefix") and (sys.base_prefix == sys.prefix):
        print("🔍 Not in a virtual environment. Creating one in 'autograder/'...")
        venv_path = os.path.dirname(os.path.abspath(__file__))

        subprocess.check_call([sys.executable, "-m", "venv", venv_path])
        print("✅ Virtual environment created.")

        if os.name == "nt":
            bin_dir = os.path.join(venv_path, "Scripts")
        else:
            bin_dir = os.path.join(venv_path, "bin")

        env = os.environ.copy()
        env["PATH"] = os.pathsep.join([bin_dir, *env.get("PATH", "").split(os.pathsep)])
        env["VIRTUAL_ENV"] = venv_path  # virtual env is right above bin directory
        env["VIRTUAL_ENV_BIN"] = bin_dir
        env["VIRTUAL_ENV_PROMPT"] = os.path.basename(venv_path)

        # Fixes encoding errors on Windows (specifically when installing packages with pip)
        env["PYTHONIOENCODING"] = "utf-8"

        interpreter_path = os.path.join(bin_dir, "python")
        result = subprocess.run([interpreter_path] + sys.argv, env=env)
        sys.exit(result.returncode)


check_virtualenv()


def install_requirements():
    import sys
    import subprocess
    import os

    # pip might need to be updated for packages to install, so let's make sure
    def check_pip_update():
        result = subprocess.run(
            [sys.executable, "-m", "pip", "list", "--outdated"],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
            text=True,
        )
        return "pip" in result.stdout

    if check_pip_update():
        print("⏳ Detected outdated pip version. Updating...")
        subprocess.check_call(
            [sys.executable, "-m", "pip", "install", "-U", "pip"],
            stdout=subprocess.DEVNULL,
        )

    REQUIREMENTS = os.path.join(os.path.dirname(__file__), "requirements.txt")

    print("⏳ Installing autograder packages (this may take a few minutes)...")

    # Packages required by the core autograder
    for package in AUTOGRADER_PACKAGES:
        subprocess.check_call(
            [sys.executable, "-m", "pip", "install", package],
            stdout=subprocess.DEVNULL,
        )

    # Assignment specific packages
    if os.path.isfile(REQUIREMENTS):
        subprocess.check_call(
            [sys.executable, "-m", "pip", "install", "-r", REQUIREMENTS],
            stdout=subprocess.DEVNULL,
        )
    
    print("✅ Autograder packages installed.")


# Install autograder packages on import
install_requirements()

def check_for_updates():
    import subprocess 

    def needs_update() -> bool:
        try:
            subprocess.check_call(["git", "rev-parse", "--is-inside-work-tree"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            subprocess.check_call(["git", "fetch", "origin"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

            origin_main_commit = subprocess.check_output(["git", "rev-parse", "origin/main"]).strip()
            result = subprocess.run(["git", "merge-base", "--is-ancestor", origin_main_commit, "HEAD"])
            return result.returncode != 0

        except subprocess.CalledProcessError:
            return False

    if needs_update():
        print("\n🔄 It looks like your assignment might be out of date. Try running:"
              "\n\n\tgit pull origin main"
              "\n\nto fetch any updates, and then re-run your code.")

check_for_updates()

from dataclasses import dataclass
from typing import Callable, List, Optional, Union
from colorama import Fore, init, Style, Back

init()


@dataclass(frozen=True)
class TestPart:
    name: str
    func: Callable[[], Union[bool, None]]
    special: bool = False


class Autograder:
    parts: List[TestPart] = []
    setup: Optional[Callable[[], None]] = None
    teardown: Optional[Callable[[], None]] = None

    def __init__(self):
        self.parts = []

    def add_part(self, name: str, func: Callable[[], bool]) -> None:
        self.parts.append(TestPart(name, func))

    def run(self) -> None:
        parts = self.parts.copy()
        if self.setup:
            parts.insert(0, TestPart("Autograder Setup", self.setup, True))
        if self.teardown:
            parts.append(TestPart("Autograder Teardown", self.teardown, True))

        failures = False
        for part in parts:
            header = f"Running test: {part.name}... 🧪".ljust(80)
            print(f"\n{Back.CYAN}{Fore.LIGHTWHITE_EX}{header}{Style.RESET_ALL}")

            result = None
            error = None

            try:
                result = part.func()
            except Exception as e:
                error = e
                result = False

            if result is None or result:
                if not part.special:
                    print(f"{Fore.GREEN}✅ {part.name} passed! 🚀 {Fore.RESET}")
            else:
                print(f"{Fore.RED}❌ {part.name} failed! 😞 {Fore.RESET}")
                if error:
                    print(f"{Style.BRIGHT}Reason:{Style.DIM} {error}{Style.RESET_ALL}")
                failures = True

                if part.special:
                    break

        if not failures:
            message = "🚀🚀🚀 Congratulations, your code passed all the autograder tests! 🚀🚀🚀"
            message = message.ljust(75)
            print(
                f"\n{Back.LIGHTGREEN_EX}{Fore.LIGHTWHITE_EX}{message}{Style.RESET_ALL}"
            )
