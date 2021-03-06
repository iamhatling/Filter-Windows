
This documentation will cover building installers + signing them

This document assumes you have Visual Studio 2017 installed. You will also need Orca, which you can get in the Windows SDK (sorry, yes, they make you download the entire thing)

# Setup build environment

## Install git

First of all, search for `Git Bash` on your computer to make sure git isn't already installed. If you don't find it, go to [https://git-scm.com/downloads](https://git-scm.com/downloads)

Download the recommended version of git.

Install it.

There are approx. seven configuration screens that follow the license screen. They can be left as they are if you wish.

## Install wix toolset and votive.

Download the latest wix toolset from [https://wixtoolset.org/releases](https://wixtoolset.org/releases).
Also make sure to install the Visual Studio 2017 Extension (which is also called votive) from the same location.

Once that's done, you can start up the solution. You should see that the setup projects loaded successfully. If they didn't, you may have to reload the project (right-click on project, and hit "Reload Project")

## Install safenet client to access smart card

[https://support.comodo.com/index.php?/Knowledgebase/Article/View/1211/66/safenet-download-for-ev-codesigning-certificates](https://support.comodo.com/index.php?/Knowledgebase/Article/View/1211/66/safenet-download-for-ev-codesigning-certificates)

Scroll to the bottom of the page for the download link, then follow instructions on page.

When you install the safenet authentication client, make sure you have all browser windows closed

## Cloning project

Now that you've got all that set up, let's clone the project.

Navigate to and open "Git Bash"

I like to have a workspace where all of my git repositories go. I like this to be "C:\git" but it doesn't really matter.

```
mkdir /c/git
cd /c/git
git clone https://github.com/cloudveiltech/Citadel-Windows.git
cd Citadel-Windows
git submodule update --init
```
## Useful git commands

Run these in Git Bash

### get bleeding edge changes
```
git pull origin master
```

### get a specific tagged version for building
First, make sure that the tag exists in the local repository
```
git fetch --all --tags --prune
```

Not sure what tags are available? Run this for a list.
```
git tag
```

Then checkout the tag by running
```
git checkout tags/v.1.6.9
```


## Building and signing installers

Open Powershell to the project root folder  
Run `.\build-installer.cmd`

Wait for the command to complete.

Once the command is done, the installer bundles will be in `.\Installers\`

If signing has been configured correctly, this should also sign the bundles for you.

## Verifying signatures
To verify that the sign tool was successful, run
```
signtool.exe verify /pa <Installer Name>.msi
```

You should get something like
```
Successfully verified: CloudVeil-1.6.12-x64.msi
```

# Other misc stuff
See CreatingAndSigningInstaller-vdproj.md for this info.
